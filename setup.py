import setuptools
from distutils.core import setup, Extension

cRandom_module = Extension("cRandom", sources=["crandom.cpp"], depends=["singleton.h"])

setup(
    name="cRandom",
    version="0.0.4",
    license="MIT",
    author="Hanjun Goo",
    author_email="goohanjun@gmail.com",
    description="Random number generation as in the Book Numerical Recipe.",
    long_description=open("README.md").read(),
    url="",
    ext_modules=[cRandom_module],
    classifiers=[
        # Tags about package
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
)
