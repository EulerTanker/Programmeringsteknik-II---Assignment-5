# slm - Small Language Model

`slm` learns a character-based language model from a text file, using k-grams (sequences of k characters), and generates new random text from it.

## Building

```
make        # builds ./slm
make clean  # removes all generated files
```

## Usage

```
./slm [-a alpha] k file length
```

`k` is the k-gram length, `file` the training text, and `length` the number of characters to output (at least k). The optional `-a alpha` sets a pseudocount (default 0); a larger value gives more random output.

Example:

```
./slm -a 0.01 3 moby_dick.txt 40
```

Invalid input gives an error message and a non-zero exit status.
