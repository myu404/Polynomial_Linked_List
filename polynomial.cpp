// ------------------------------------------------ PROG 03 -------------------------------------------------------

// Michael Yu, CSS 501

// Created on: 11/15/2021

// Date of Last Modification: 11/15/2021

// ---------------------------------------------------------------------------------------------------------------

// Purpose - Implement ADT Polynomial class as a linked list

#include "polynomial.h"

// ------------------------------------operator<<-----------------------------------------------
// Description

// operator<<: friend function defining output stream operation on Polynomial objects
// preconditions: output stream from <iostream> and Polynomial object
// postconditions: Polynomial object data is formatted as Cn * x^n + Cn-1 * X^n-1 + ... C1 * X + C0 and sent to output stream
//                  Nothing is sent to stream for empty Polynomial object

// --------------------------------------------------------------------------------------------
ostream& operator<<( ostream &output, const Polynomial& p )
{
    if (p.size == 0)
    {
        output << 0;
    }
    else
    {
        bool activeStream = false;

        auto* current = p.head->next;

        while (current != p.head)
        {
            auto coeff = current->coeff;
            auto power = current->power;

            // All subsequent Polynomial Term is preceded by arithmetic symbol
            if (activeStream)
            {
                output << ((coeff > 0) ? " + " : " - ");
            }

            // Ensure correct formatting for highest/leading Polynomial power and coefficient
            if (!activeStream && coeff < 0.0) output << "-";

            if (power != 0)
            {
                if (std::abs(coeff) != 1.0) output << std::abs(coeff);

                if (power == 1) output << "x";
                else output << "x^" << power;
            }
            else
            {
                output << std::abs(coeff);
            }

            current = current->next;

            // Flag that highest/leading Polynomial Term has been printed to output stream
            if (!activeStream) activeStream = true;
        }
    }
    return output;
}

// Member functions

// ------------------------------------Polynomial-----------------------------------------------
// Description

// Polynomial: default constructor
// preconditions: none
// postconditions: instantiate Polynomial object as a 0-degree polynomial with 0.0 coefficient

// --------------------------------------------------------------------------------------------
Polynomial::Polynomial()
    : size(0),
    head(new Term)
{
    // Ensure that head dummy node is pointing to itself
    // 0-degree polynomial with 0.0 coefficient do not get a Term node
    clear();
}

// ------------------------------------Polynomial-----------------------------------------------
// Description

// Polynomial: copy constructor
// preconditions: Polynomial object
// postconditions: Deep copy of Polynomial object

// --------------------------------------------------------------------------------------------
Polynomial::Polynomial( const Polynomial& p )
    : Polynomial()
{
    // Copy assign the object to Polynomial p
    *this = p;
}

// ------------------------------------~Polynomial-----------------------------------------------
// Description

// ~Polynomial: destructor when Polynomial object is going out of scope or deleted
// preconditions: none
// postconditions: remove Polynomial object from stack or heap memory

// --------------------------------------------------------------------------------------------
Polynomial::~Polynomial( )
{
    // Deallocate all Term nodes and delete head
    clear();
    delete head;
}

// ------------------------------------degree-----------------------------------------------
// Description

// degree: member function that returns the highest polynomial degree
// preconditions: none
// postconditions: returns the degree of a polynomial or 0 if empty Polynomial

// --------------------------------------------------------------------------------------------
int Polynomial::degree( ) const // returns the degree of a polynomial
{
    return (size > 0) ? head->next->power : 0;
}

// ------------------------------------coefficient-----------------------------------------------
// Description

// coefficient: member function that returns the coefficient of the x^power term
// preconditions: integer value of x^power term
// postconditions: returns the coefficient of x^power term or 0 if x^power term doesn't exist in polynomial

// --------------------------------------------------------------------------------------------
double Polynomial::coefficient( const int power ) const
{
    auto* current = head->next;
    while (current != head)
    {
        // Break out of loop if current->power < power. Indicates coefficient of x^power doesn't exist
        if (current->power < power) break;

        if (current->power == power) return current->coeff;

        current = current->next;
    }

    return 0.0;
}

// ------------------------------------changeCoefficient-----------------------------------------------
// Description

// changeCoefficient: member function that replaces the coefficient of the x^power term with the newCoefficient
// preconditions: x^power term must be greater than or equal to 0
// postconditions: replaces coefficient of x^power term with newCoefficient. If newCoefficient is 0, removes x^power term.
//                  If newCoefficient is non-zero and x^power term doesn't current exist, add x^power term to polynomial

// --------------------------------------------------------------------------------------------
bool Polynomial::changeCoefficient( const double newCoefficient, const int power )
{
    auto isChanged = false;

    if (power >= 0)
    {
        auto* current = head->next;

        while (current != head)
        {
            if (current->power <= power)
            {
                // Update coefficient if x^power exist
                if (current->power == power)
                {
                    if (newCoefficient == 0) remove(current);
                    else current->coeff = newCoefficient;
                }
                else
                {
                    // If current->power doesn't exist in Polynomial and less than current power, then insert before current
                    if (newCoefficient != 0) insert(current, newCoefficient, power);
                }

                isChanged = true;
                break;
            }

            current = current->next;
        }

        // If haven't changed, then insertion belongs at head of Polynomial
        if (!isChanged && newCoefficient != 0)
        {
            insert(head, newCoefficient, power);
            isChanged = true;
        }
    }

    return isChanged;
}

// Arithmetic operators

// ------------------------------------operator+-----------------------------------------------
// Description

// operator+: member function defining how polynomials are added using +. Calls changeCoefficient to update coefficient sums
// preconditions: this object is the left operand and the right operand is another polynomial object
// postconditions: sum of the two polynomial objects

// --------------------------------------------------------------------------------------------
Polynomial Polynomial::operator+( const Polynomial& p ) const
{
    auto polynomial = *this;

    polynomial += p;

    return polynomial;
}

// ------------------------------------operator------------------------------------------------
// Description

// operator-: member function defining how polynomials are subtracted using -. Calls changeCoefficient to update coefficient sums
// preconditions: this object is the left operand and the right operand is another polynomial object
// postconditions: difference of the two polynomial objects

// --------------------------------------------------------------------------------------------
Polynomial Polynomial::operator-( const Polynomial& p ) const
{
    auto polynomial = *this;

    polynomial -= p;

    return polynomial;
}

// Boolean comparison operators

// ------------------------------------operator==-----------------------------------------------
// Description

// operator==: member function checks if another polynomial object is equal to this object
// preconditions: this object is the left operand and the right operand is another polynomial object
// postconditions: boolean indicating equality

// --------------------------------------------------------------------------------------------
bool Polynomial::operator==( const Polynomial& p ) const
{
    if (size != p.size) return false;

    auto* currentThis = head->next;
    auto* currentP = p.head->next;

    while (currentThis != head)
    {
        if ((currentThis->power != currentP->power) || (currentThis->coeff != currentP->coeff)) return false;
        currentThis = currentThis->next;
        currentP = currentP->next;
    }

    return true;
}

// ------------------------------------operator!=-----------------------------------------------
// Description

// operator!=: member function checks if another polynomial object is not equal to this object
// preconditions: this object is the left operand and the right operand is another polynomial object
// postconditions: boolean indicating inequality

// --------------------------------------------------------------------------------------------
bool Polynomial::operator!=( const Polynomial& p ) const
{
    return !(*this == p);
}

// Assignment operators

// ------------------------------------operator=-----------------------------------------------
// Description

// operator=: copy assignment function
// preconditions: Polynomial object
// postconditions: Assigns current Polynomial object to the input Polynomial object. Performs deep copy of Polynomial object

// --------------------------------------------------------------------------------------------
Polynomial& Polynomial::operator=( const Polynomial& p )
{
    if (p != *this)
    {
        clear();
        auto* current = p.head->next;
        while (current != p.head)
        {
            insert(head, current->coeff, current->power);
            current = current->next;
        }
    }

    return *this;
}

// ------------------------------------operator+=----------------------------------------------
// Description

// operator+=: member function defining how polynomials are added using + and update the object itself with the resulting sum.
//              Calls changeCoefficient to update coefficient sums
// preconditions: this object is the left operand and the right operand is another polynomial object
// postconditions: sum of the two polynomial objects

// --------------------------------------------------------------------------------------------
Polynomial& Polynomial::operator+=( const Polynomial& p )
{
    auto* current = p.head->next;
    while (current != p.head)
    {
        /*
        if (current->next != head && (currentP->power < current->power)) current = current->next;
        else
        {
            if (currentP->power == current->power) changeCoefficient(current->coeff + currentP->coeff, current->power);
            else changeCoefficient(currentP->coeff, currentP->power);
            currentP = currentP->next;
        }
         */
        changeCoefficient(coefficient(current->power) + current->coeff, current->power);
        current = current->next;
    }

    return *this;
}

// ------------------------------------operator-=----------------------------------------------
// Description

// operator-=: member function defining how polynomials are subtracted using - and update the object itself with the resulting difference.
//              Calls changeCoefficient to update coefficient sums
// preconditions: this object is the left operand and the right operand is another polynomial object
// postconditions: difference of the two polynomial objects

// --------------------------------------------------------------------------------------------
Polynomial& Polynomial::operator-=( const Polynomial& p )
{
    auto* current = p.head->next;
    while (current != p.head)
    {
        changeCoefficient(coefficient(current->power) - current->coeff, current->power);
        current = current->next;
    }
    return *this;
}

// ------------------------------------insert----------------------------------------------
// Description

// insert: private member function that inserts new polynomial Term node into polynomial object with newCoefficient and power
//          just before/in-front of polynomial Term node pointed by position pos pointer
// preconditions: valid pos pointer that points to an existing Term node in polynomial object
// postconditions: added new Term node before the Term node pointed by pos

// --------------------------------------------------------------------------------------------
bool Polynomial::insert( Term* pos, const double newCoefficient, const int power )
{
    // try-catch block to ensure dynamic memory allocation is possible
    try
    {
        auto* term = new Term;
        term->coeff = newCoefficient;
        term->power = power;

        // Find the Polynomial position for insertion
        auto* before = head;
        auto* current = head->next;
        while (current != head)
        {
            if (current->power < power) break;
            before = current;
            current = current->next;
        }

        term->next = current;
        term->prev = before;
        current->prev = term;
        before->next = term;

        ++size;
        return true;
    }
    catch (std::bad_alloc&)
    {
        return false;
    }
}

// ------------------------------------remove----------------------------------------------
// Description

// remove: private member function that removes Term node from polynomial object
// preconditions: valid Term node in polynomial.
// postconditions: Term node removed from polynomial object and deleted from heap memory

// --------------------------------------------------------------------------------------------
bool Polynomial::remove( Term* pos )
{
    pos->next->prev = pos->prev;
    pos->prev->next = pos->next;
    delete pos;
    --size;
    return true;
    /*
    auto* current = head->next;
    while (current != head)
    {
        if (current->coeff == pos->coeff && current->power == pos->power)
        {
            current->next->prev = current->prev;
            current->prev->next = current->next;
            delete current;
            --size;
            return true;
        }
        current = current->next;
    }
    return false;
    */
}

// ------------------------------------clear----------------------------------------------
// Description

// clear: private member function that safely remove Term nodes from Polynomial object
// preconditions: none
// postconditions: empty Polynomial object where all Term nodes are deleted from heap memory

// --------------------------------------------------------------------------------------------
void Polynomial::clear()
{
    if (size > 0)
    {
        Term* currentTerm = head->next;
        Term* nextTerm = currentTerm->next;
        while (currentTerm != head)
        {
            remove(currentTerm);
            currentTerm = nextTerm;
            nextTerm = nextTerm->next;
        }
    }

    // Empty Polynomial, where head points to itself
    head->next = head;
    head->prev = head;
}
