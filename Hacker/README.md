### Global Normalization for Streaming Speech Recognition in a Modular Framework

The following paper introduces the Globally Normalized Autoregressive Transducer (GNAT) for addressing the label bias problem in streaming speech recognition. A non-streaming ASR model’s alignment score has access to the entire input x, while for streaming, it only has access to the prefix of the input feature sequence till the current time frame. Since complete input is available at the start,  locally normalized  model scores can be interpreted as conditional probability distribution. But this doesn't hold for streaming speech recognition. And hence we use Global Normalization to tackle this issue.

Paper provides a framework for calculating the global normalization using WFST's. Details about this can be found in the paper.

We implemented the segment of this pipeline intended for computing the global normalization score based on some provided weights. 

We don't actually use the neural network for training the weights, but instead we use two different kinds of intialisation of weights, random and uniform. And then we apply the global normalisation to get the probability distribution over the strings. 

We contructed the context and alignment WFSTs using the OpenFst library. We also show the state diagram corresponding to these WFSTs.


### Dependencies involved:
* OpenFst 1.8.3
* Eigen 

### Instructions for running the code:

To construct the desired FSTs and calculation of globalnorm run the following command:
```
make globalnorm
./globalnorm

```
After running the make for globalnorm, run the following command to see the FSTs that are created:
```
make fst
```
