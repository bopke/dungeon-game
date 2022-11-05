# Dungeon game

Soon™

## Building

Currently, runs only on linux and macOS due to usage of ncurses, windows support planned for future.

### Installing ncurses

First, before we install project, make sure you have ncurses installed.

#### Ubuntu

```shell
apt install libncurses5-dev
```

#### MacOS

```shell
brew install ncurses
```

### Building project

```shell
cmake .
make
```

## Testing

After building project, run

```shell
./dungeon_game_tests
```
