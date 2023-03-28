#!/bin/bash

cd ../firmware/lib
doxygen ../../doxygen/yali-doc

mv ../../doc/html ../../html
rm -rf ../../doc
mv ../../html ../../doc
