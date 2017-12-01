#!/usr/bin/python3
import subprocess

output = subprocess.check_output(['git', 'clang-format-5.0', 
    '--binary', 'clang-format-5.0', '--commit', 'HEAD~1', '--diff'])
if output.strip().lower() in [b'no modified files to format',
                              b'clang-format did not modify any files']:
    print(output.strip().decode('utf-8'))
    exit(0)
else:
    print('Code style does not match clang-format')
    print(output.strip().decode('utf-8'))
    exit(1)
