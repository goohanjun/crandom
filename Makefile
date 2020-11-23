cRandom:
	python setup.py build_ext --inplace

test:
	python test.py

all: cRandom test

setup:
	# pip install setuptools wheel
	python setup.py sdist bdist_wheel
	# pip install twine
	# python -m twine upload dist/*

up:
	rm -rf ./dist
	python setup.py build_ext --inplace
	python setup.py sdist bdist_wheel
	pip install twine
	python -m twine upload dist/*
