FROM gcc:4.9
COPY . /test
RUN ls test
WORKDIR /test
RUN g++ -o output test.cpp
CMD ["./output"]