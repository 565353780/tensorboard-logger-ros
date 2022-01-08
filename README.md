# TensorBoard Logger

Only support `scalar`, `histogram`, `image`, `audio` `text` and `projector` at the moment.

## Install

```bash
sudo apt install libprotobuf-dev protobuf-compiler
```

```bash
> mkdir build && cd build && cmake .. && cmake --build . -j
> cd .. && mkdir demo && ./tensorboard_logger_test
> tensorboard --logdir .  # try adding --load_fast=false if you don't see projector tab
```

