from setuptools import setup
from setuptools.dist import Distribution

class BinaryDistribution(Distribution):
	def is_pure(self):
		return False

setup(name='tokenex',
      version='0.1.2',
      description='A flexible tokenizer',
      url='http://aka.ms/tokenex',
      author='Thang Duong',
      author_email='thduon@microsoft.com',
      license='Microsoft Internal Only',
      packages=['tokenex'],
      package_data={
           'tokenex': ['tokenizer_so.so', 'tokenizer.dll'],
      },
      include_package_data=True,
      distclass=BinaryDistribution,
      zip_safe=False)
