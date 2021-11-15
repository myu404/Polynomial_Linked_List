// ------------------------------------------------ PROG 03 -------------------------------------------------------

// Michael Yu, CSS 501

// Created on: 11/15/2021

// Date of Last Modification: 11/15/2021

// ---------------------------------------------------------------------------------------------------------------

// Purpose - Implement ADT Polynomial class as a linked list

// A Polynomial class                                  // Munehiro Fukuda
#ifndef POLYNOMIAL_H                                   // CSS342
#define POLYNOMIAL_H
#include <iostream>
#include <string>
using namespace std;

 struct Term {     // a term on the sparse polynomial
    double coeff;   // the coefficient of each term
    int power;      // the degree of each term
    Term *prev;     // a pointer to the previous higher term
    Term *next;     // a pointer to the next lower term
  };

class Polynomial {

    // ------------------------------------operator<<-----------------------------------------------
    // Description

    // operator<<: friend function defining output stream operation on Polynomial objects
    // preconditions: output stream from <iostream> and Polynomial object
    // postconditions: Polynomial object data is formatted as Cn * x^n + Cn-1 * X^n-1 + ... C1 * X + C0 and sent to output stream
    //                  Nothing is sent to stream for empty Polynomial object

    // --------------------------------------------------------------------------------------------
    friend ostream& operator<<( ostream &output, const Polynomial& p );

 public:
  // Member functions
    // ------------------------------------Polynomial-----------------------------------------------
    // Description

    // Polynomial: default constructor
    // preconditions: none
    // postconditions: instantiate Polynomial object as a 0-degree polynomial with 0.0 coefficient

    // --------------------------------------------------------------------------------------------
    Polynomial( );

    // ------------------------------------Polynomial-----------------------------------------------
    // Description

    // Polynomial: copy constructor
    // preconditions: Polynomial object
    // postconditions: Deep copy of Polynomial object

    // --------------------------------------------------------------------------------------------
  Polynomial( const Polynomial& p );

    // ------------------------------------~Polynomial-----------------------------------------------
    // Description

    // ~Polynomial: destructor when Polynomial object is going out of scope or deleted
    // preconditions: none
    // postconditions: remove Polynomial object from stack or heap memory

    // --------------------------------------------------------------------------------------------
    ~Polynomial( );

    // ------------------------------------degree-----------------------------------------------
    // Description

    // degree: member function that returns the highest polynomial degree
    // preconditions: none
    // postconditions: returns the degree of a polynomial or 0 if empty Polynomial

    // --------------------------------------------------------------------------------------------
    int degree( ) const; // returns the degree of a polynomial

    // ------------------------------------coefficient-----------------------------------------------
    // Description

    // coefficient: member function that returns the coefficient of the x^power term
    // preconditions: integer value of x^power term
    // postconditions: returns the coefficient of x^power term or 0 if x^power term doesn't exist in polynomial

    // --------------------------------------------------------------------------------------------
    double coefficient( const int power ) const;

    // ------------------------------------changeCoefficient-----------------------------------------------
    // Description

    // changeCoefficient: member function that replaces the coefficient of the x^power term with the newCoefficient
    // preconditions: x^power term must be greater than or equal to 0
    // postconditions: replaces coefficient of x^power term with newCoefficient. If newCoefficient is 0, removes x^power term.
    //                  If newCoefficient is non-zero and x^power term doesn't current exist, add x^power term to polynomial

    // --------------------------------------------------------------------------------------------
    bool changeCoefficient( const double newCoefficient, const int power );
                 // replaces the coefficient of the x^power term

  // Arithmetic operators

    // ------------------------------------operator+-----------------------------------------------
    // Description

    // operator+: member function defining how polynomials are added using +. Calls changeCoefficient to update coefficient sums
    // preconditions: this object is the left operand and the right operand is another polynomial object
    // postconditions: sum of the two polynomial objects

    // --------------------------------------------------------------------------------------------
    Polynomial operator+( const Polynomial& p ) const;

    // ------------------------------------operator------------------------------------------------
    // Description

    // operator-: member function defining how polynomials are subtracted using -. Calls changeCoefficient to update coefficient sums
    // preconditions: this object is the left operand and the right operand is another polynomial object
    // postconditions: difference of the two polynomial objects

    // --------------------------------------------------------------------------------------------
    Polynomial operator-( const Polynomial& p ) const;

  // Boolean comparison operators

    // ------------------------------------operator==-----------------------------------------------
    // Description

    // operator==: member function checks if another polynomial object is equal to this object
    // preconditions: this object is the left operand and the right operand is another polynomial object
    // postconditions: boolean indicating equality

    // --------------------------------------------------------------------------------------------
    bool operator==( const Polynomial& p ) const;

    // ------------------------------------operator!=-----------------------------------------------
    // Description

    // operator!=: member function checks if another polynomial object is not equal to this object
    // preconditions: this object is the left operand and the right operand is another polynomial object
    // postconditions: boolean indicating inequality

    // --------------------------------------------------------------------------------------------
    bool operator!=( const Polynomial& p ) const;

  // Assignment operators

    // ------------------------------------operator=-----------------------------------------------
    // Description

    // operator=: copy assignment function
    // preconditions: Polynomial object
    // postconditions: Assigns current Polynomial object to the input Polynomial object. Performs deep copy of Polynomial object

    // --------------------------------------------------------------------------------------------
    Polynomial& operator=( const Polynomial& p );

    // ------------------------------------operator+=----------------------------------------------
    // Description

    // operator+=: member function defining how polynomials are added using + and update the object itself with the resulting sum.
    //              Calls changeCoefficient to update coefficient sums
    // preconditions: this object is the left operand and the right operand is another polynomial object
    // postconditions: sum of the two polynomial objects

    // --------------------------------------------------------------------------------------------
    Polynomial& operator+=( const Polynomial& p );

    // ------------------------------------operator-=----------------------------------------------
    // Description

    // operator-=: member function defining how polynomials are subtracted using - and update the object itself with the resulting difference.
    //              Calls changeCoefficient to update coefficient sums
    // preconditions: this object is the left operand and the right operand is another polynomial object
    // postconditions: difference of the two polynomial objects

    // --------------------------------------------------------------------------------------------
    Polynomial& operator-=( const Polynomial& p );

private:
  int size;         // # terms in the sparse polynomial
  Term *head;       // a pointer to the doubly-linked circular list of
                    // sparse polynomial

    // ------------------------------------insert----------------------------------------------
    // Description

    // insert: private member function that inserts new polynomial Term node into polynomial object with newCoefficient and power
    //          just before/in-front of polynomial Term node pointed by position pos pointer
    // preconditions: valid pos pointer that points to an existing Term node in polynomial object
    // postconditions: added new Term node before the Term node pointed by pos

    // --------------------------------------------------------------------------------------------
    bool insert( Term* pos, const double newCoefficient, const int power );

    // ------------------------------------remove----------------------------------------------
    // Description

    // remove: private member function that removes Term node from polynomial object
    // preconditions: valid Term node in polynomial.
    // postconditions: Term node removed from polynomial object and deleted from heap memory

    // --------------------------------------------------------------------------------------------
    bool remove( Term* pos );

    // ------------------------------------clear----------------------------------------------
    // Description

    // clear: private member function that safely remove Term nodes from Polynomial object
    // preconditions: none
    // postconditions: empty Polynomial object where all Term nodes are deleted from heap memory

    // --------------------------------------------------------------------------------------------
    void clear();
};

#endif
