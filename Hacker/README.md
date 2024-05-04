### [Global Normalization for Streaming Speech Recognition in a Modular Framework](https://arxiv.org/pdf/2205.13674)

The following paper introduces the Globally Normalized Autoregressive Transducer (GNAT) for addressing the label bias problem in streaming speech recognition. A non-streaming ASR model’s alignment score has access to the entire input x, while for streaming, it only has access to the prefix of the input feature sequence till the current time frame. Since complete input is available at the start,  locally normalized  model scores can be interpreted as conditional probability distribution. But this doesn't hold for streaming speech recognition. And hence we use Global Normalization to tackle this issue.

Paper provides a framework for calculating the global normalization using WFST's. Details about this can be found in the paper.

We implemented the segment of this pipeline intended for computing the global normalization score based on some provided weights. 

For demonstration purposes we use two different kinds of weight intialisation i.e random and uniform instead of obtaining them from a neural network as a result of training, and then apply the global normalisation to get the probability distribution over all the possible strings. 

We constructed the context and alignment FSAs using the [OpenFst](https://www.openfst.org/twiki/bin/view/FST/WebHome) library. We also show the state diagram corresponding to these FSAs. As an example, the state diagram corresponding to alignment FST for T = 4 is:


<br>
The state diagram for a context FSA for n = 2 is as shown:



### Dependencies involved:
* OpenFst 1.8.3
* Eigen 

### Instructions for running the code:
Download the two folders *includes* and *link-dep* from the following [link](https://drive.google.com/drive/folders/1qa_rMOMRlXKRw8JsL9Z5iS8fEGTC-IP_?usp=sharing) and keep them in the directory:
The directory structure should be as follows: <br><br>
. <br>
|_ Alignment.cpp <br>
|_Context.cpp <br>
|_GlobalNorm.cpp <br>
|_Makefile <br>
|_create_links.sh <br>
|_show_fst.sh <br>
|_support.h <br>
|_includes <br>
|_link-dep<br>

To construct the desired FSTs and calculation of globalnorm run the following command:
```
make globalnorm
./globalnorm

```
After running the make for globalnorm, run the following command to see the FSTs that are created:
```
make fst
```
