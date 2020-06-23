
C-MINUS COMPILATION: D:/QTproject/cminusProject/testFile/treeSOURCE2.C

	19: reserved word: int
	19: ID, name= x
	19: [
	19: NUM, val= 10
	19: ]
	19: ;
	21: reserved word: int
	21: ID, name= minloc
	21: (
	21: reserved word: int
	21: ID, name= a
	21: [
	21: ]
	21: ,
	21: reserved word: int
	21: ID, name= low
	21: ,
	21: reserved word: int
	21: ID, name= high
	21: )
	22: {
	22: reserved word: int
	22: ID, name= i
	22: ;
	22: reserved word: int
	22: ID, name= s
	22: ;
	22: reserved word: int
	22: ID, name= k
	22: ;
	23: ID, name= k
	23: =
	23: ID, name= low
	23: ;
	24: ID, name= s
	24: =
	24: ID, name= a
	24: [
	24: ID, name= low
	24: ]
	24: ;
	25: ID, name= i
	25: =
	25: ID, name= low
	25: +
	25: NUM, val= 1
	25: ;
	26: reserved word: while
	26: (
	26: ID, name= i
	26: <
	26: ID, name= high
	26: )
	27: {
	27: reserved word: if
	27: (
	27: ID, name= a
	27: [
	27: ID, name= i
	27: ]
	27: <
	27: ID, name= s
	27: )
	28: {
	28: ID, name= s
	28: =
	28: ID, name= a
	28: [
	28: ID, name= i
	28: ]
	28: ;
	29: ID, name= k
	29: =
	29: ID, name= i
	29: ;
	30: }
	31: ID, name= i
	31: =
	31: ID, name= i
	31: +
	31: NUM, val= 1
	31: ;
	32: }
	33: reserved word: return
	33: ID, name= k
	33: ;
	34: }
	36: reserved word: void
	36: ID, name= sort
	36: (
	36: reserved word: int
	36: ID, name= a
	36: [
	36: ]
	36: ,
	36: reserved word: int
	36: ID, name= low
	36: ,
	36: reserved word: int
	36: ID, name= high
	36: )
	37: {
	37: reserved word: int
	37: ID, name= i
	37: ;
	37: reserved word: int
	37: ID, name= k
	37: ;
	38: ID, name= i
	38: =
	38: ID, name= low
	38: ;
	39: reserved word: while
	39: (
	39: ID, name= i
	39: <
	39: ID, name= high
	39: -
	39: NUM, val= 1
	39: )
	40: {
	40: reserved word: int
	40: ID, name= t
	40: ;
	41: ID, name= k
	41: =
	41: ID, name= minloc
	41: (
	41: ID, name= a
	41: ,
	41: ID, name= i
	41: ,
	41: ID, name= high
	41: )
	41: ;
	42: ID, name= t
	42: =
	42: ID, name= a
	42: [
	42: ID, name= k
	42: ]
	42: ;
	43: ID, name= a
	43: [
	43: ID, name= k
	43: ]
	43: =
	43: ID, name= a
	43: [
	43: ID, name= i
	43: ]
	43: ;
	44: ID, name= a
	44: [
	44: ID, name= i
	44: ]
	44: =
	44: ID, name= t
	44: ;
	45: ID, name= i
	45: =
	45: ID, name= i
	45: +
	45: NUM, val= 1
	45: ;
	46: }
	47: reserved word: return
	47: ;
	48: }
	50: reserved word: void
	50: ID, name= main
	50: (
	50: reserved word: void
	50: )
	51: {
	51: reserved word: int
	51: ID, name= i
	51: ;
	52: ID, name= i
	52: =
	52: NUM, val= 0
	52: ;
	53: reserved word: while
	53: (
	53: ID, name= i
	53: <
	53: NUM, val= 10
	53: )
	54: {
	54: ID, name= x
	54: [
	54: ID, name= i
	54: ]
	54: =
	54: ID, name= input
	54: (
	54: )
	54: ;
	55: ID, name= i
	55: =
	55: ID, name= i
	55: +
	55: NUM, val= 1
	55: ;
	56: ID, name= i
	56: =
	56: NUM, val= 0
	56: ;
	57: reserved word: while
	57: (
	57: ID, name= i
	57: <
	57: NUM, val= 10
	57: )
	58: {
	58: ID, name= output
	58: (
	58: ID, name= x
	58: [
	58: ID, name= i
	58: ]
	58: )
	58: ;
	59: ID, name= i
	59: =
	59: ID, name= i
	59: +
	59: NUM, val= 1
	59: ;
	60: }
	61: }
	62: reserved word: return
	62: ;
	63: }
	64: EOF
Syntax tree:

  int Var Declaration: x[10]
  int function Declaration: minloc
    int Param: a[]
    int Param: low
    int Param: high
    Compound stmt
      int Var Declaration: i
      int Var Declaration: s
      int Var Declaration: k
      Exp stmt
        Assign: =
          Id: k
          Id: low
      Exp stmt
        Assign: =
          Id: s
          Id: a
            Id: low
      Exp stmt
        Assign: =
          Id: i
          Op: +
            Id: low
            Const: 1
      While stmt
        Op: <
          Id: i
          Id: high
        Compound stmt
          If stmt
            Op: <
              Id: a
                Id: i
              Id: s
            Compound stmt
              Exp stmt
                Assign: =
                  Id: s
                  Id: a
                    Id: i
              Exp stmt
                Assign: =
                  Id: k
                  Id: i
          Exp stmt
            Assign: =
              Id: i
              Op: +
                Id: i
                Const: 1
      Return stmt
        Id: k
  void function Declaration: sort
    int Param: a[]
    int Param: low
    int Param: high
    Compound stmt
      int Var Declaration: i
      int Var Declaration: k
      Exp stmt
        Assign: =
          Id: i
          Id: low
      While stmt
        Op: <
          Id: i
          Op: -
            Id: high
            Const: 1
        Compound stmt
          int Var Declaration: t
          Exp stmt
            Assign: =
              Id: k
              Call stmt: minloc
                Id: a
                Id: i
                Id: high
          Exp stmt
            Assign: =
              Id: t
              Id: a
                Id: k
          Exp stmt
            Assign: =
              Id: a
                Id: k
              Id: a
                Id: i
          Exp stmt
            Assign: =
              Id: a
                Id: i
              Id: t
          Exp stmt
            Assign: =
              Id: i
              Op: +
                Id: i
                Const: 1
      Return stmt
  void function Declaration: main
    void Param: void
    Compound stmt
      int Var Declaration: i
      Exp stmt
        Assign: =
          Id: i
          Const: 0
      While stmt
        Op: <
          Id: i
          Const: 10
        Compound stmt
          Exp stmt
            Assign: =
              Id: x
                Id: i
              Call stmt: input
          Exp stmt
            Assign: =
              Id: i
              Op: +
                Id: i
                Const: 1
          Exp stmt
            Assign: =
              Id: i
              Const: 0
          While stmt
            Op: <
              Id: i
              Const: 10
            Compound stmt
              Exp stmt
                Call stmt: output
                  Id: x
                    Id: i
              Exp stmt
                Assign: =
                  Id: i
                  Op: +
                    Id: i
                    Const: 1
      Return stmt
