#!/usr/bin/env python
from __future__ import print_function
import fileinput
from shutil import copyfile
import sys, os

cxxflags = ''
cxxflags += '-lpthread'

if (not os.path.isdir(os.getcwd() + '/src/')):
	print("Invalid dir, no src")
	quit();

src_files = os.listdir(os.getcwd() + '/src/')
sources = ''
for src_file in src_files:
	if src_file.endswith(".cpp"):
		sources += '${SRC_DIR}/' + src_file + ' '
	if src_file.endswith(".c"):
		sources += '${SRC_DIR}/' + src_file + ' '
copyfile(os.path.dirname(os.path.realpath(__file__)) + '/Makefile',os.getcwd() + '/Makefile')
for line in fileinput.input(os.getcwd() + '/Makefile', inplace=True):
	print(line.replace('%%SOURCES%%', sources), end='')
for line in fileinput.input(os.getcwd() + '/Makefile', inplace=True):
	print(line.replace('%%CXXFLAGS%%', cxxflags), end='')
	
