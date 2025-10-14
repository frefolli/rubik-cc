project('rubik',
  ['cpp'],
  version : '0.1',
  default_options : ['warning_level=3', 'werror=true', 'cpp_std=c++23'])

include = include_directories('./include')
raylib = dependency('raylib')

executable('rubik', [
    'src/main.cc'
  ], dependencies: [raylib],
  include_directories: include)
