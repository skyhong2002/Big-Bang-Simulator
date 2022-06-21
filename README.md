# Big-Bang-Simulator
A Bang board game simulator written in C by team 10

## How to Play?

1. clone this repo and cd by typing in your command line:

```sh
git clone https://github.com/skyhong2002/Big-Bang-Simulator.git
cd Big-Bang-Simulator
```

2. make it and run it 

```
make
./main # -p to show help message
```

## Support OS

### Operational

- Ubuntu 20.04 LTS
- Ubuntu 22.04 LTS

### Not supported

- MacOS
`rand()` issue, see [this](https://stackoverflow.com/questions/64680033/rand-behaves-differently-between-macos-and-linux)

## Known issue

segmentation fault when bot trying to play a certain card, very rarely occurs.  
Gatlings and Indians could be the problem, but we still can't find it.

## Special Thanks

- [@JacobLinCool](https://github.com/JacobLinCool) for tech support and assistants
