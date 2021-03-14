#!/usr/bin/env python3

import subprocess
from logging import Logger, basicConfig, getLogger
from pathlib import Path
from typing import List
import argparse
import pyperclip
import re

logger = getLogger(__name__)  # type: Logger


def get_gcc_version():
    proc = subprocess.Popen(['gcc', '--version'],
                            stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
    for line in proc.stdout:
        match = re.match(r'gcc \(GCC\) (.*)\s*', line.decode())
        if match:
            return match[1]
    raise NameError('No version was found')


def create_dummy_headers():
    dummy_include_path = Path(__file__).resolve().parent / 'dummy_headers'
    (dummy_include_path).mkdir(exist_ok=True)
    (dummy_include_path/'bits').mkdir(exist_ok=True)
    (dummy_include_path/'ext').mkdir(exist_ok=True)
    (dummy_include_path/'ext/pb_ds').mkdir(exist_ok=True)

    gcc_version = get_gcc_version()
    include_pattern = re.compile(r'#include <(.*)>')
    bits_include_path = Path(
        '/usr/include/c++/{}/x86_64-pc-linux-gnu/bits/'.format(gcc_version))

    bits_stdcpp = bits_include_path / 'stdc++.h'
    with open(bits_stdcpp) as f:
        for line in f:
            match = include_pattern.match(line)
            if match:
                name = match[1]
                Path.touch(dummy_include_path / name)
                with open(dummy_include_path / name, mode='w') as f2:
                    f2.write('#pragma INCLUDE <{}>'.format(name))

    bits_extcpp = bits_include_path / 'extc++.h'
    with open(bits_extcpp) as f:
        for line in f:
            match = include_pattern.match(line)
            if match:
                name = match[1]
                Path.touch(dummy_include_path / name)
                with open(dummy_include_path / name, mode='w') as f2:
                    f2.write('#pragma INCLUDE <{}>'.format(name))


def beautify(str):
    headers = set()
    include_pattern = re.compile('#pragma INCLUDE <(.*)>')
    output = ''
    for line in str.splitlines():
        if re.match('^\s*$', line):
            continue
        match = include_pattern.match(line)
        if match:
            headers.add('#include <{}>'.format(match[1]))
        else:
            output += line + '\n'
    return '\n'.join(headers) + '\n' + output


def expand(args):
    include_directories = args.include_directories
    logger.info('include_directories: {}'.format(include_directories))

    defined_macros = args.defined_macros
    logger.info('defined_macros: {}'.format(defined_macros))

    source_file_path = Path(args.source_file_name)
    if not source_file_path.is_absolute():
        source_file_path = Path.cwd() / source_file_path
    source_file_directory = source_file_path.parent
    output_file_path = source_file_path.with_name(
        source_file_path.stem + '_submission' + source_file_path.suffix)
    tmp_file_path = source_file_path.with_name(
        source_file_path.stem + '_tmp' + source_file_path.suffix)
    logger.info('source_file_path: {}'.format(source_file_path))
    logger.info('output_file_path: {}'.format(output_file_path))

    dummy_include_path = Path(__file__).resolve().parent / 'dummy_headers'
    commands = ['g++', str(source_file_path), '-o', tmp_file_path, '-std=c++17',
                '-E', '-P', '-I', dummy_include_path]  # type: List[str]
    for macro in defined_macros:
        commands.append('-D')
        commands.append(macro)
    for directory in include_directories:
        commands.append('-I')
        commands.append(str(directory))
    subprocess.run(commands, cwd=source_file_directory)

    output = beautify(open(str(tmp_file_path)).read())
    logger.debug('output: {}'.format(output))
    tmp_file_path.unlink()

    with open(str(output_file_path), mode='w') as f:
        f.write(output)
    if args.clipboard:
        pyperclip.copy(output)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Expand included libraries')
    parser.add_argument('source_file_name', help='Name of source')
    parser.add_argument('-I', '--include_directories', nargs='*', default=[])
    parser.add_argument('-D', '--defined_macros', nargs='*', default=[])
    parser.add_argument(
        '-L', '--log_level', choices=['DEBUG', 'INFO', 'WARNING', 'ERROR', 'CRITICAL'], default='WARNING')
    parser.add_argument('-C', '--clipboard',
                        action='store_true', help='Copy to clipboard')

    args = parser.parse_args()

    basicConfig(
        format="[%(levelname)s] %(message)s",
        datefmt="%H:%M:%S",
        level=args.log_level,
    )

    create_dummy_headers()
    expand(args)
