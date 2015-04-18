// cube.h - class to capture boolean logic cube representation, consistent with the Perkowski Cube Calculus Machine
//
//  Copyright Addy Gronquist 2015


class bcube {
    int nVars;
    bool (*literals)[2];
  public:
    bcube (int, char *);
};
