from setuptools import setup
from catkin_pkg.python_setup import generate_distutils_setup

# Fetch values from package.xml
setup_args = generate_distutils_setup(
    packages=['position_2d_correction'],
    package_dir={'': 'src'},
)

setup(**setup_args)
