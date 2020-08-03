<p align="center">
  <img height="100" src="img/logo.png"/> 
</p>

`cgol` is a modern C++ implementation of Conway's Game of Life.

* **Runs in the terminal** - uses the terminal width/height as the grid size
* Reads from run-length encoding (`.rle`) pattern files (See `samples/`)
* MIT License

## Quick Start

```bash
git clone git@github.com:p-ranav/cgol
cd cgol
mkdir build && cd build
cmake .. && make
```

### Usage

```bash
./cgol <pattern.rle>

# example: ./cgol ../samples/glider.rle
```

## Samples

### Gosper Glider Gun

<p>
  <img src="img/gosper_glider_gun.gif"/> 
</p>

### Oscillator Synthesis

<p>
  <img src="img/oscillator_synthesis.gif"/> 
</p>

### Spaceships

<p>
  <img src="img/spaceships.gif"/> 
</p>

### All known c/3 spaceships up to 50 bits

<p>
  <img src="img/c3_orthogonal.gif"/> 
</p>

### Stargate

<p>
  <img src="img/stargate.gif"/> 
</p>

### Queen Bee

<p>
  <img src="img/queen_bee.gif"/> 
</p>

### Fermat Prime Calculator

<p>
  <img src="img/fermat.gif"/> 
</p>

## Contributing
Contributions are welcome, have a look at the [CONTRIBUTING.md](CONTRIBUTING.md) document for more information.

## License
The project is available under the [MIT](https://opensource.org/licenses/MIT) license.
