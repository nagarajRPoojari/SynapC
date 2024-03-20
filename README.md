
<p align="center">
  <a href="https://github.com/AMAI-GmbH/AI-Expert-Roadmap">
    <img src="https://github.com/nagarajRPoojari/SynapC/assets/116948655/288c4145-8433-439b-8cf7-0ccf8837d874" width="96" height="96" "
>
  </a>


  
  <h1 align="center">SynapC</h1>
  <p align="center">A minimalistic neural network library in C</p>
  <p align="center">
      <a href="" target="_blank"><img src="https://img.shields.io/github/license/nagarajRPoojari/Gluon-AI.svg" style="display: inherit;"/></a>
      <a href="https://www.linkedin.com/shareArticle?mini=true&url=https://i.am.ai/roadmap&title=&><img src="https://img.shields.io/badge/post-blue.svg?logo=linkedin&logoColor=white" style="display: inherit;"/></a>
      <a href="https://github.com/nagarajRPoojari/Gluon-AI"><img src="https://img.shields.io/github/issues/nagarajRPoojari/Gluon-AI.svg" style="display: inherit;"/></a>
<a href="https://opensource.org/licenses/MIT/" target="_blank"></a>
  </p>
  <br>
</p>


Latest version: 0.0.5  
Author:Nagaraj poojari  
Email: np137270@gmail.com 


## Description

SynapC is a light weight neural network library written in C and provides API for python.


## Installation
```bash
  pip install synapc==0.0.5
```
</p>

## Usage
```python
  import synapc
  model=synapc.init(3) # initalize a FFNN network
  synapc.add(model,2)  # add dense layers 
  synapc.add(model,4)
  synapc.add(model,4)
  synapc.compile(model,X_train) # compile
  synapc.train(model,X_train,y_train,40) # train
```

## Results
SynapC is twice as fast as scratch implementation using only numpy.
<div>
  <img src="https://github.com/nagarajRPoojari/SynapC/assets/116948655/59d15ba9-dd17-4e4e-be1d-fa3363f2b53a" width="300">
  <img src="https://github.com/nagarajRPoojari/SynapC/assets/116948655/15438148-a6c2-440a-ad5a-6c5ae542a71e" width="300">
</div>


## Rate and Review

If you find this module helpful, please consider leaving a review and rating on the [PyPI](https://pypi.org/project/synapc/).

## Contributions

We welcome contributions from the community! If you'd like to contribute to SynapC, please follow these steps:

1. Fork this repository.
2. Create a new branch for your feature/bugfix.
3. Make your changes and ensure tests pass.
4. Submit a pull request explaining the changes you've made.


## License

This extension is released under the MIT License. For more information, see [LICENSE](LICENSE).

---
