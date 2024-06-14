# War Simulator

## About
The classic [card game War](https://en.wikipedia.org/wiki/War_(card_game)).
This program allows you to simulate full games or step through turn-by-turn

## Building
Build the project by using the included `makefile` by running: `make`. The
resulting binary `war_simulator` will be placed in the `bin/` directory.

## Usage
You can run the program by running:
```bash
./bin/war_simulator
```

If you want to run it in turn-by-turn mode tack on the `-m` flag:
```bash
./bin/war_simulator -m
```

The help menu can be viewed by passing the `-h` flag:
```bash
./bin/war_simulator -h
```
