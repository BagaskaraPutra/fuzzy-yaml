# fuzzy-yaml

Fuzzy logic control C++ library loaded from a YAML config file

This is a refactored version of the source code originally used in the following [paper](https://arxiv.org/abs/2012.10867)
>B. P. Putra, G. S. Mahardika, M. Faris, and A. I. Cahyadi, "**Humanoid Robot Pitch Axis Stabilization using Linear Quadratic Regulator with Fuzzy Logic and Capture Point**", arXiv [cs.RO]. 2021.

Instead of using arrays for storing the linguistic sets, key-value maps are utilized for a more natural way of accessing them by calling their respective string key.

**Note**: As of May 2024, this library is only applicable for the Mamdani type-1 fuzzy inference system with:  

- trapezoid and triangle membership functions, and
- 2-dimensional rule table with AND operation

However, contributions for additional features are welcome.

## Dependencies

1. [CMake](https://cmake.org/download/)

1. [Boost](https://www.boost.org/)

1. [yaml-cpp](https://github.com/jbeder/yaml-cpp)

## Build & Run

1. Make sure you have installed the dependencies.

1. Open a new command line terminal. Clone the repository

    ```bash
    git clone https://github.com/BagaskaraPutra/fuzzy-yaml.git
    ```

1. Build the project using CMake.

    ```bash
    cd fuzzy-yaml
    mkdir build
    cd build
    cmake ..
    make
    ```

1. The example executable files will be generated in the `build/examples/` directory.

1. Run the executable, for example:

    ```bash
    ./examples/multiAnklePitch
    ```

1. If you wish to run other YAML config files, add the file path after the executable. For example:

    ```bash
    ./examples/anklePitch ../config/allTrapezoidAnklePitch.yaml
    ```

## Tutorial

A typical YAML config file for the `fuzzy-yaml` library consists of three main nodes:

```yaml
inputVariables:
  ...
outputVariables:
  ...
ruleBase:
  ...
```

The `inputVariables` node is structured as:

```yaml
inputVariables:
  Crisp input variable 1:
    memberships:
      Linguistic fuzzy input variable 1.1:
        type: ...
        ...
      Linguistic fuzzy input variable 1.2:
        type: ...
        ...
  Crisp input variable 2:
    memberships:
      Linguistic fuzzy input variable 2.1:
        type: ...
        ...
      Linguistic fuzzy input variable 2.2:
        type: ...
        ...
    ...
```

Similarly for the `outputVariables` node:

```yaml
outputVariables:
  Crisp output variable 1:
    memberships:
      Linguistic fuzzy output variable 1.1:
        type: ...
        ...
    defuzzifier: ...
  Crisp output variable 2:
    memberships:
      Linguistic fuzzy output variable 2.1:
        type: ...
        ...
    defuzzifier: ...
  ...
```

For the `outputVariables` node, we have an additional `defuzzifier` method parameter.
As of now, only the `centroid` defuzzifier method is available.

On the other hand, the `ruleBase` node consists of the following structure:

```yaml
ruleBase:
  Crisp output variable 1:
    # rules
    ...
  Crisp output variable 2:
    # rules
    ...
```

For now, the `ruleBase` only accepts the 2-dimensional table format. For example in the `examples/anklePitch.yaml` file, the rule table

```yaml
ruleBase:
  Kp:
    row_variable: Angle
    row_values: [NegativeHigh, Negative, Positive, PositiveHigh]
    column_variable: AngularVelocity
    column_values: [Negative, Average, Positive]
    operator: AND
    table: 
      - [High, High, High]
      - [Medium, Medium, Medium]
      - [Zero, Zero, Zero]
      - [High, High, High]
```

is equivalent to having the following 12 fuzzy rules:

- **IF** Angle is NegativeHigh **AND** AngularVelocity is Negative **THEN** Kp is High
- **IF** Angle is Negative **AND** AngularVelocity is Negative **THEN** Kp is Medium
- **IF** Angle is Positive **AND** AngularVelocity is Negative **THEN** Kp is Zero
- ...
- **IF** Angle is PositiveHigh **AND** AngularVelocity is Positive **THEN** Kp is High

## Citation

If you intend to use this code in your work, you may cite it as:

```bib
@misc{putra2021humanoid,
      title={Humanoid Robot Pitch Axis Stabilization using Linear Quadratic Regulator with Fuzzy Logic and Capture Point}, 
      author={Bagaskara Primastya Putra and Gabrielle Satya Mahardika and Muhammad Faris and Adha Imam Cahyadi},
      year={2021},
      eprint={2012.10867},
      archivePrefix={arXiv},
      primaryClass={cs.RO}
}
```
