
C-MINUS COMPILATION: E:/QTproject/cminusProject/testFile/treeSOURCE1.C

	2: reserved word: int
	2: ID, name= s
	2: ;
	3: reserved word: int
	3: ID, name= gcd
	3: (
	3: reserved word: int
	3: ID, name= u
	3: ,
	3: reserved word: int
	3: ID, name= v
	3: )
	4: {
	5: reserved word: int
	5: ID, name= x
	5: ;
	5: reserved word: int
	5: ID, name= y
	5: ;
	6: {
	6: reserved word: int
	6: ID, name= u
	6: ;
	6: ID, name= u
	6: =
	6: ID, name= v
	6: +
	6: NUM, val= 1
	6: ;
	6: ID, name= x
	6: =
	6: ID, name= v
	6: *
	6: (
	6: ID, name= u
	6: )
	6: ;
	6: }
	7: reserved word: if
	7: (
	7: ID, name= v
	7: ==
	7: NUM, val= 0
	7: )
	7: reserved word: return
	7: ID, name= u
	7: >
	7: ID, name= y
	7: ;
	8: reserved word: else
	8: reserved word: return
	8: ID, name= gcd
	8: (
	8: ID, name= v
	8: ,
	8: ID, name= u
	8: -
	8: ID, name= u
	8: /
	8: ID, name= v
	8: *
	8: ID, name= v
	8: )
	8: ;
	9: }
	10: reserved word: void
	10: ID, name= main
	10: (
	10: reserved word: void
	10: )
	11: {
	12: reserved word: int
	12: ID, name= x
	12: ;
	12: reserved word: int
	12: ID, name= y
	12: ;
	12: reserved word: int
	12: ID, name= b
	12: [
	12: NUM, val= 10
	12: ]
	12: ;
	12: {
	12: reserved word: int
	12: ID, name= a
	12: ;
	12: }
	13: ID, name= x
	13: =
	13: ID, name= input
	13: (
	13: )
	13: ;
	13: ID, name= y
	13: =
	13: ID, name= input
	13: (
	13: )
	13: ;
	14: ID, name= output
	14: (
	14: ID, name= gcd
	14: (
	14: ID, name= x
	14: ,
	14: ID, name= y
	14: )
	14: )
	14: ;
	15: reserved word: return
	15: ;
	16: }
	17: EOF
Syntax tree:

  int Var Declaration: s
  int function Declaration: gcd
    int Param: u
    int Param: v
    Compound stmt
      int Var Declaration: x
      int Var Declaration: y
      Compound stmt
        int Var Declaration: u
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
          Op: >
            Id: u
            Id: y
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
      Compound stmt
        int Var Declaration: a
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
