A Practice of Computing Diagram In A Symbolic Style
==========

Tensorflow is a popular framework for deep learning. Its computing diagram mainly includes the following two units: forward propagation and backward propagation.
Meanwhile, the programming style in arithmetic operations are divided into two types, namely, imperative style and symbolic style.  The imperative style is easy to understand, that is, it runs according to the original logic, like 
``` imperative style
x = 100 + 99
print (x)
```

On the contrary, a symbolic computing is compiled without any output only after putting the value to each input that to be calculated. Data flow will be formed in advance to a graph model and output will be generated as the last step. It looks like,
``` symbolic style
import tensorflow as tf
x = tf.constant(100, name='input_x')
y = tf.constant(99, name='input_y')
f = tf.add(x, y, name='add_xy')
sess = tf.Session()
print sess.run(f)
sess.close()
```

Among the well-known deep learning frameworks, torch is imperative while Caffe and Mxnet is a hybrid of two modes. But Tensorflow adopts symbolic programming completely. Symbolic programming initialize variables first, and then establishes a data flow diagram (computing graph). The computing graph specifies the calculation relationship between the variables.

In this project, a simple computing graph is built for arithmetic operations, "+", "-", "*" and "/". There are a few advantages to use symbolic style in Tensorflow.

- #1 Computing process is structured closely to what happens when our brain is computing. For example, when we calculate x + y/z, we actually calculate y/z first, and then x to be added.
- #2 This diagram is convenient for us to extract any intermediate results. According to the flow structure of Tensorflow, when we calculate the total  losses, we can get the values of W and B at any time. Without it, if you want to get the value of W and B, you have to recalculate the previous steps.
- #3 More importantly, the computing graph is also convenient for the derivation computing in the backward propagation.

There are another two tips, one is parallelization. Because computing graph is an abstraction of computing process, the relationship between nodes depends on its dependency. Therefore, independent computing can be done in parallel, and distributed computing can be built in cluster environment.
Another one is portability for TensorFlow specifically. Because the diagram is a language-independent representation. In TensorFlow, protobuf is used to store the graph, so all C++, python, Jave or other languages can parse the graph.  


LICENSE
=======

The code which makes up this project is licensed under the MIT/X11 license.

Copyright (c) 2020 Chao (Chase) Xu
