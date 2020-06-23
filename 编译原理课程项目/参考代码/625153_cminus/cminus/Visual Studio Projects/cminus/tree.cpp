#include <iostream>
#include <string>

using namespace ::std;

#include "common.h"
#include "tree.h"
#include "symbol.h"
#include "lexer.h"
#include "parser.h"

extern int lineno;
extern symbol_table symtbl;

tree parse_tree;

int tree::node_seq = 0;
int tree::temp_var_seq = 0;
int tree::label_seq = 0;

void Node::output(void)
{
	cout.setf(ios_base::left);
	cout.width(2);
	cout << seq << ": ";
	switch(kind)
	{
	case STMT_NODE:
		{
			string names[] = { "if", "while", "input", "print", "compound" };
			cout.width(40);
			cout << names[kind_kind] + " statement,";
			break;
		}
	case EXPR_NODE:
		{
			string names[] = { "Type Specifier", "Expr", "Not Expr", "Array", "Const Declaration", "ID Declaration" };
			string types[] = { "Notype", "integer", "boolean", "char" };
			string opnames[] = { "&&", "||", "!", "=", "==", "<", "<=", ">", ">=", "!=",
				"+", "-", "*", "/" };

			cout.width(20);
			cout << names[kind_kind] + ',';
			cout.width(10);
			cout << types[type] + ',';
			cout.width(10);
			switch (kind_kind)
			{
			case TYPE_EXPR:
				cout << "";
				break;
			case NOT_EXPR:
			case OP_EXPR:
				{
					char tmp[100];
					if (attr.op >= PLUS && attr.op <= OVER)
						sprintf(tmp, "op: %s, t%d", opnames[attr.op - AND].c_str(), temp_var);
					else
						sprintf(tmp, "op: %s", opnames[attr.op - AND].c_str());
					cout << tmp;
				}
				break;
			case CONST_EXPR:
				if (type == Integer)
				{
					char tmp[100];
					sprintf(tmp, "value:%d, ", attr.vali);
					cout << tmp;
				}
				else
					cout << string("value: '") + attr.valc + "',";
				break;
			case ID_EXPR:
				cout << "symbol: " + symtbl.getname(attr.symtbl_seq);
				break;
			}
			break;
		}
	case DECL_NODE:
		{
			string names[] = { "Var Declaration, ", "Array Declaration, " };
			cout.width(40);
			cout << names[kind_kind];
			break;
		}
	}

	cout << "Children: ";
	for (int i = 0; i < MAX_CHILDREN; i++)
		if (NULL == children[i])
			break;
		else
		{
			cout << children[i]->seq << " ";
		}
	if (i)
	{
		i--;
		for (Node *child = children[i]->sibling; child; child = child->sibling)
			cout << child->seq << " ";
	}

	cout << endl;
}


void tree::type_check(Node *t)
{
	if (t->type != Notype)
		return;

	if (t->kind == STMT_NODE)
	{
		if (t->kind_kind == IF_STMT || t->kind_kind == WHILE_STMT)
			if (t->children[0]->type != Boolean)
			{
				cerr << "Bad boolean type at line: " << t->lineno << endl;
				exit(1);
			}
			else
				return;
	}
	if (t->kind != EXPR_NODE)
		return;

	if (t->kind_kind != OP_EXPR && t->kind_kind != NOT_EXPR)
		return;

	Node *arg1 = t->children[0];
	Node *arg2 = t->children[1];
	if (t->attr.op == NOT)
	{
		if (arg1->type != Boolean)
		{
			cerr << "Bad type at line: " << t->lineno << endl;
			exit(1);
		}
		t->type = arg1->type;
	}
	else if (t->attr.op >= AND && t->attr.op <= OR)
	{
		if (arg1->type != Boolean || arg2->type != Boolean)
		{
			cerr << "Bad type at line: " << t->lineno << endl;
			exit(1);
		}
		t->type = arg1->type;
	}
	else if (t->attr.op >= EQ && t->attr.op <= NE)
	{
		if (arg1->type != Integer || arg2->type != Integer)
		{
			cerr << "Bad type at line: " << t->lineno << endl;
			exit(1);
		}
		t->type = Boolean;
	}
	else if (t->attr.op >= PLUS && t->attr.op <= OVER || t->attr.op == ASSIGN)
	{
		if (arg1->type != Integer || arg2->type != Integer)
		{
			cerr << "Bad type at line: " << t->lineno << endl;
			exit(1);
		}
		t->type = arg1->type;
	}


	return;
}

void tree::get_temp_var(Node *t)
{
	if (t->kind != EXPR_NODE)
		return;
	if (t->attr.op < PLUS || t->attr.op > OVER)
		return;

	Node *arg1 = t->children[0];
	Node *arg2 = t->children[1];

	if (arg1->kind_kind == OP_EXPR)
		temp_var_seq--;
	if (arg2 && arg2->kind_kind == OP_EXPR)
		tree::temp_var_seq--;
	t->temp_var = tree::temp_var_seq;
	tree::temp_var_seq++;
}

Node* tree::NewRoot(int kind, int kind_kind, NodeAttr attr, int type,
				   Node *child1, Node *child2, Node *child3, Node *child4)
{
	Node *t = new Node;
	
	if (NULL == t)
		cerr << "Out of memory at line %d\n" << lineno;
	else
	{
		t->kind = kind;
		t->kind_kind = kind_kind;
		t->attr = attr;
		t->type = type;
		t->children[0] = child1;
		t->children[1] = child2;
		t->children[2] = child3;
		t->children[3] = child4;
		t->lineno = lineno;
		t->seq = tree::node_seq++;
		t->sibling = NULL;
		t->label.begin_label = "";
		t->label.next_label = "";
		t->label.true_label = "";
		t->label.false_label = "";
		root = t;
		type_check(t);
		get_temp_var(t);

#ifdef PARSE_DEBUG
		t->output();
#endif
	}
	return t;
}

string tree::new_label(void)
{
	char tmp[20];

	sprintf(tmp, "@%d", tree::label_seq);
	tree::label_seq++;
	return tmp;
}

void tree::stmt_get_label(Node *t)
{
	switch (t->kind_kind)
	{
	case COMP_STMT:
		{
			Node *last;
			Node *p;
			for (p = t->children[0]; p->kind == DECL_NODE; p = p->sibling) ;

			p->label.begin_label = t->label.begin_label;
			for (; p; p = p->sibling)
			{
				last = p;
				recursive_get_label(p);
			}

			t->label.next_label = last->label.next_label;
			if (t->sibling)
				t->sibling->label.begin_label = t->label.next_label;
		}
		break;

	case IF_STMT:
		{
			Node *e = t->children[0];
			Node *s1 = t->children[1];
			Node *s2 = t->children[2];

			e->label.true_label = new_label();

			if (t->label.next_label == "")
				t->label.next_label = new_label();
			s1->label.next_label = t->label.next_label;
			if (t->sibling)
				t->sibling->label.begin_label = t->label.next_label;

			if (s2)
			{
				e->label.false_label = new_label();
				s2->label.next_label = t->label.next_label;
			}
			else
			{
				e->label.false_label = t->label.next_label;
			}
			recursive_get_label(e);
			recursive_get_label(s1);
			if (s2)
				recursive_get_label(s2);
		}
		break;

	case WHILE_STMT:
		{
			Node *e = t->children[0];
			Node *s = t->children[1];

			if (t->label.begin_label == "")
				t->label.begin_label = new_label();
			s->label.next_label = t->label.begin_label;

			s->label.begin_label = e->label.true_label = new_label();

			if (t->label.next_label == "")
				t->label.next_label = new_label();
			e->label.false_label = t->label.next_label;
			if (t->sibling)
				t->sibling->label.begin_label = t->label.next_label;

			recursive_get_label(e);
			recursive_get_label(s);
		}
	}
#ifdef PARSE_DEBUG
	cout << "node " << t->seq << ":" << t->label.begin_label << ", " << t->label.next_label << endl;
#endif
}

void tree::expr_get_label(Node *t)
{
	if (t->type != Boolean)
		return;

#ifdef PARSE_DEBUG
	cout << "node " << t->seq << ": "<< t->label.true_label << ", " << t->label.false_label << endl;
#endif
	Node *e1 = t->children[0];
	Node *e2 = t->children[1];
	switch (t->attr.op)
	{
	case AND:
		e1->label.true_label = new_label();
		e2->label.true_label = t->label.true_label;
		e1->label.false_label = e2->label.false_label = t->label.false_label;
		break;

	case OR:
		e1->label.false_label = new_label();
		e2->label.false_label = t->label.false_label;
		e1->label.true_label = e2->label.true_label = t->label.true_label;
		break;

	case NOT:
		e1->label.true_label = t->label.false_label;
		e1->label.false_label = t->label.true_label;
		break;
	}
	if (e1)
		recursive_get_label(e1);
	if (e2)
		recursive_get_label(e2);
}

void tree::recursive_get_label(Node *t)
{
	if (t->kind == STMT_NODE)
		stmt_get_label(t);
	else if (t->kind == EXPR_NODE)
		expr_get_label(t);
}

void tree::get_label(void)
{
	Node *p = root;

	p->label.begin_label = "_start";
	recursive_get_label(p);
}

void tree::gen_header(ostream &out)
{
	out << "\t.586" << endl;
    out << "\t.model flat, stdcall" << endl;
	out << "\toption casemap :none" << endl;
	out << endl;
	out << "\tinclude \\masm32\\include\\windows.inc" << endl;
	out << "\tinclude \\masm32\\include\\user32.inc" << endl;
	out << "\tinclude \\masm32\\include\\kernel32.inc" << endl;
	out << "\tinclude \\masm32\\include\\masm32.inc" << endl;
	out << endl;
	out << "\tincludelib \\masm32\\lib\\user32.lib" << endl;
	out << "\tincludelib \\masm32\\lib\\kernel32.lib" << endl;
	out << "\tincludelib \\masm32\\lib\\masm32.lib" << endl;
}

void tree::gen_decl(ostream &out, Node *t)
{
	out << endl << endl << "\t.data" << endl;
	
	for (; t->kind == DECL_NODE; t = t->sibling)
	{
		for (Node *p = t->children[1]; p; p = p->sibling)
			if (p->type == Integer)
				out << "\t\t_" << symtbl.getname(p->attr.symtbl_seq) << " DWORD 0" << endl;
			else if (p->type == Char)
				out << "\t\t_" << symtbl.getname(p->attr.symtbl_seq) << " BYTE 0" << endl;
	}
	
	for (int i = 0; i < temp_var_seq; i++)
	{
		out << "\t\tt" <<  i << " DWORD 0" << endl;
	}

	out << "\t\tbuffer BYTE 128 dup(0)" << endl;
	out << "\t\tLF BYTE 13, 10, 0" << endl;
}

void tree::stmt_gen_code(ostream &out, Node *t)
{
	if (t->kind_kind == COMP_STMT)
	{
		for (int i = 0; t->children[i]; i++)
		{
			recursive_gen_code(out, t->children[i]);
			for (Node *p = t->children[i]->sibling; p; p = p->sibling)
				recursive_gen_code(out, p);
		}
	}
	else if (t->kind_kind == WHILE_STMT)
	{
		if (t->label.begin_label != "")
			out << t->label.begin_label << ":" << endl;
		recursive_gen_code(out, t->children[0]);
		recursive_gen_code(out, t->children[1]);
		out << "\tjmp " << t->label.begin_label << endl;
	}
	else if (t->kind_kind == INPUT_STMT)
	{
		Node *v = t->children[0];
		out << "\tinvoke StdIn, ADDR buffer, 127" << endl;
		out << "\tinvoke StripLF, ADDR buffer" << endl;
		out << "\tinvoke atodw, ADDR buffer" << endl;
		out << "\tMOV ";
		if (v->kind_kind == ID_EXPR)
			out << "_" << symtbl.getname(v->attr.symtbl_seq);
		out << ", eax" << endl;	
	}
	else if (t->kind_kind == PRINT_STMT)
	{
		Node *v = t->children[0];
		out << "\tinvoke dwtoa, ";
		if (v->kind_kind == ID_EXPR)
			out << "_" << symtbl.getname(v->attr.symtbl_seq);
		out << ", ADDR buffer" << endl;
		out << "\tinvoke StdOut, ADDR buffer" << endl;
		out << "\tinvoke StdOut, ADDR LF" << endl;
	}
}

void tree::expr_gen_code(ostream &out, Node *t)
{
	Node *e1 = t->children[0];
	Node *e2 = t->children[1];
	switch (t->attr.op)
	{
	case ASSIGN:
		if (t->label.begin_label != "")
			out << t->label.begin_label << ":" << endl;
		recursive_gen_code(out, e1);
		recursive_gen_code(out, e2);
		out << "\tMOV eax, ";
		if (e2->kind_kind == ID_EXPR)
			out << "_" << symtbl.getname(e2->attr.symtbl_seq);
		else if (e2->kind_kind == CONST_EXPR)
			out << e2->attr.vali;
		else out << "t" << e2->temp_var;
		out << endl;
		out << "\tMOV ";
		if (e1->kind_kind == ID_EXPR)
			out << "_" << symtbl.getname(e1->attr.symtbl_seq);
		else out << "t" << e1->temp_var;
		out << ", eax" << endl;
		break;

	case PLUS:
		out << "\tMOV eax, ";
		if (e1->kind_kind == ID_EXPR)
			out << "_" << symtbl.getname(e1->attr.symtbl_seq);
		else if (e1->kind_kind == CONST_EXPR)
			out << e1->attr.vali;
		else out << "t" << e1->temp_var;
		out << endl;
		out << "\tADD eax, ";
		if (e2->kind_kind == ID_EXPR)
			out << "_" << symtbl.getname(e2->attr.symtbl_seq);
		else if (e2->kind_kind == CONST_EXPR)
			out << e2->attr.vali;
		else out << "t" << e2->temp_var;
		out << endl;
		out << "\tMOV t" << t->temp_var << ", eax" << endl;
		break;
	case LT:
		out << "\tMOV eax, ";
		if (e1->kind_kind == ID_EXPR)
			out << "_" << symtbl.getname(e1->attr.symtbl_seq);
		else if (e1->kind_kind == CONST_EXPR)
			out << e1->attr.vali;
		else out << "t" << e1->temp_var;
		out << endl;
		out << "\tCMP eax, ";
		if (e2->kind_kind == ID_EXPR)
			out << "_" << symtbl.getname(e2->attr.symtbl_seq);
		else if (e2->kind_kind == CONST_EXPR)
			out << e2->attr.vali;
		else out << "t" << e2->temp_var;
		out << endl;
		out << "\tjl " << t->label.true_label << endl;
		out << "\tjmp " << t->label.false_label << endl;
		break;
	}
}

void tree::recursive_gen_code(ostream &out, Node *t)
{
	if (t->kind == STMT_NODE)
	{
		stmt_gen_code(out, t);
	}
	else if (t->kind == EXPR_NODE && (t->kind_kind == OP_EXPR || t->kind_kind == NOT_EXPR))
	{
		expr_gen_code(out, t);
	}
}

void tree::gen_code(ostream &out)
{
	gen_header(out);
	Node *p = root->children[0];
	if (p->kind == DECL_NODE)
		gen_decl(out, p);
	out << endl << endl << "\t.code" << endl;
	recursive_gen_code(out, root);
	if (root->label.next_label != "")
		out << root->label.next_label << ":" << endl;
	out << "\tinvoke ExitProcess, 0" << endl;
	out << "end " << root->label.begin_label << endl;
}