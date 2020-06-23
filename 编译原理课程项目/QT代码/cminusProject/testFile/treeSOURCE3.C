
C-MINUS COMPILATION: D:/QTproject/cminusProject/testFile/treeSOURCE3.C

	65: reserved word: int
	65: ID, name= s
	65: ;
	66: reserved word: int
	66: ID, name= gcd
	66: (
	66: reserved word: int
	66: ID, name= u
	66: ,
	66: reserved word: int
	66: ID, name= v
	66: )
	67: {
	68: reserved word: int
	68: ID, name= x
	68: ;
	68: reserved word: int
	68: ID, name= y
	68: ;
	69: ID, name= u
	69: =
	69: ID, name= v
	69: +
	69: NUM, val= 1
	69: ;
	69: ID, name= x
	69: =
	69: ID, name= v
	69: *
	69: ID, name= u
	69: ;
	70: reserved word: if
	70: (
	70: ID, name= v
	70: ==
	70: NUM, val= 0
	70: )
	70: reserved word: return
	70: ID, name= u
	70: ;
	71: reserved word: else
	71: reserved word: return
	71: ID, name= gcd
	71: (
	71: ID, name= v
	71: ,
	71: ID, name= u
	71: -
	71: ID, name= u
	71: /
	71: ID, name= v
	71: *
	71: ID, name= v
	71: )
	71: ;
	72: }
	73: reserved word: void
	73: ID, name= main
	73: (
	73: reserved word: void
	73: )
	74: {
	75: reserved word: int
	75: ID, name= x
	75: ;
	75: reserved word: int
	75: ID, name= y
	75: ;
	75: reserved word: int
	75: ID, name= b
	75: [
	75: NUM, val= 10
	75: ]
	75: ;
	76: reserved word: void
	76: ID, name= p
	76: ;
	77: ID, name= p
	77: =
	77: NUM, val= 1
	77: ;
	78: ID, name= x
	78: =
	78: ID, name= input
	78: (
	78: )
	78: ;
	78: ID, name= y
	78: =
	78: ID, name= input
	78: (
	78: )
	78: ;
	80: ID, name= output
	80: (
	80: ID, name= gcd
	80: (
	80: ID, name= x
	80: ,
	80: ID, name= y
	80: )
	80: )
	80: ;
	82: reserved word: return
	82: ;
	83: }
	84: EOF
Syntax tree:

  int Var Declaration: s
  int function Declaration: gcd
    int Param: u
    int Param: v
    Compound stmt
      int Var Declaration: x
      int Var Declaration: y
      Exp stmt
        Assign: =
          Id: u
          Op: +
            Id: v
            Const: 1
      Exp stmt
        Assign: =
          Id: x
          Op: *
            Id: v
            Id: u
      If stmt
        Op: ==
          Id: v
          Const: 0
        Return stmt
          Id: u
        Return stmt
          Call stmt: gcd
            Id: v
            Op: -
              Id: u
              Op: *
                Op: /
                  Id: u
                  Id: v
                Id: v
  void function Declaration: main
    void Param: void
    Compound stmt
      int Var Declaration: x
      int Var Declaration: y
      int Var Declaration: b[10]
      void Var Declaration: p
      Exp stmt
        Assign: =
          Id: p
          Const: 1
      Exp stmt
        Assign: =
          Id: x
          Call stmt: input
      Exp stmt
        Assign: =
          Id: y
          Call stmt: input
      Exp stmt
        Call stmt: output
          Call stmt: gcd
            Id: x
            Id: y
      Return stmt
