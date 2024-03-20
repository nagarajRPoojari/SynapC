
from setuptools import setup, find_packages , Extension
 
c_src_files=[
    'src/activation.c',
    'src/loss.c',
    'src/ndarray.c',
    'src/metric.c',
    'src/nn.c',
    'src/num.c',
    'src/dense_layer.c',
    'synap.c'
]

extensions=[Extension('synapc',c_src_files)]

setup(
    name='synapc', 
    version='0.2',  
    author='Nagaraj Poojari',
    author_email='np137270@email.com',
    description='A minimalistic neural network library in C',
    long_description='',
    long_description_content_type='text/markdown',
    ext_modules=extensions,
    url='https://github.com/nagarajRPoojari/SynapC', 
    packages=find_packages(),
    install_requires=[
        'numpy',
        'scipy',
    ],
    classifiers=[
        'Programming Language :: Python :: 3',
        'License :: OSI Approved :: MIT License',
        'Operating System :: OS Independent',
    ],
)
