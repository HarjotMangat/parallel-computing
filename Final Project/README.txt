=====================================
*   Harjot Mangat                   *
*   EECS 245 - Parallel Computing   *
*   MNIST_on_GPU.py                 *
=====================================

This program is a simple implementation of a neural network that predicts handwritten digits from 0 to 9.
This is implemented in Pytorch to see the performance of CUDA vs CPU.
This runs with the following imports:
	matplotlib.pyplot
	torch
	torchvision
	torch.profiler

This was tested with torch 1.12.1, torchvision 0.13.1.
The Pytorch version will also need the relevant GPU drivers and CUDA version. An easy way to get all of this is from: https://pytorch.org/

This program has three options: train, benchmark, profile

train - this option runs an initial test of the model's accuracy and then runs 6 epochs of training, with a test run in between each epoch of training

benchmark - this option runs a benchmark of one training iteration. For GPU warmup and other reasons of the Timer function, this will be run roughly 3 times before printing the time it took to run

profile - this option profiles the model during one training run. This profiler has high overhead, so this might take a while to run. The profile printed at the end will be sorted by highest 'cuda_memory_usage'