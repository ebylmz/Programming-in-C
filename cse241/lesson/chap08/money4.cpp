/* Operator Overloading: Overloading operator<< */

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

/** Stream extraction operator returns ostream object (cout in this example)
 *  cout << "I have " << amount << " in my purse.\n";
 *  ((cout << "I have ") << amount) << " in my purse.\n";   returns cout and output "I have "
 *  (cout << amount) << " in my purse.\n";                  returns cout and output value of amount
 *  (cout << " in my purse.\n";                             returns cout and output "I have "
 *  cout;                                                   Since there are no more << operators, the process ends.
 */

/**
 * If you want the operators to behave as expected for cin, cout, and fi le I/O, then the value
 * returned should be of type istream for input and ostream for output, and the value should
 * be returned by reference.
 * 
 * The operators do not need to be friends but cannot be members of the class being input or output. 
 * 
 * If you have enough accessor and mutator functions, you can overload >> and << as
 * nonfriend functions. However, it is natural and more efficient to define them as friends.
 */

class Money {
    public:
        Money ();
        Money (double amount);
        Money (int theDollars, int theCents);
        Money (int theDollars);

        double getAmount () const;
        int getDollars () const;
        int getCents () const;

        /* There is no const keyword at the end of the fuction decleration
           because friends functions are not member of that class */

        /* friends keyword means: this global  function is my friend and can access all my data (private) */
        const Money & operator= (const Money & other);
        // operator= must be overloaded as member operator. If there is no
        // compiler automaticly copies right-hand-side to left-hand-side
        
        friend const Money operator+ (const Money & amount1, const Money & amount2);
        friend const Money operator- (const Money & amount1, const Money & amount2);
        friend bool operator== (const Money & amount1, const Money & amount2);
        friend bool operator!= (const Money & amount1, const Money & amount2);
        friend const Money operator- (const Money & amount);
        friend ostream & operator<< (ostream & outStream, const Money & amount);
        friend istream & operator>> (istream & inStream, Money & amount);
    private:
        /* Take total amount as double and parse it to dollars and cents as int variables */
        int dollars;
        int cents;
        int dollarsPart (double amount) const;  
        int centsPart (double amount) const;
        int round (double number) const;
};


int main (void) {
    Money yourAmount, myAmount(10, 9);
    cout << "Enter an amount of money: ";
    cin >> yourAmount;
    
    cout << "Your amount is " << yourAmount << endl;
    cout << "My amount is " << myAmount << endl;
    
    if (yourAmount == myAmount)
        cout << "We have the same amounts.\n";
    else
        cout << "One of us is richer.\n";
    
    cout << yourAmount << " + " << myAmount << " equals " << yourAmount + myAmount << endl;
    cout << yourAmount << " - " << myAmount << " equals " << yourAmount - myAmount << endl;

    return 0;
}

Money::Money () : dollars(0), cents(0)
{/* Body intentionally empty. */}

Money::Money (double amount) : dollars(dollarsPart(amount)), cents(centsPart(amount)) 
{/* Body intentionally empty. */}

Money::Money (int theDollars, int theCents) {
    if ((theDollars >= 0 && theCents >= 0) || (theDollars <= 0 && theCents <= 0)) {
        dollars = theDollars;
        cents = theCents;
    }
    else {
        cout << "Inconsistent money data.\n";
        exit(1);
    }
}

Money::Money (int theDollars) : dollars(theDollars), cents(0) 
{/* Body intentionally empty. */}


/* No need to implement this operation overload is automaticly done */
const Money & Money::operator= (const Money & other) {
    dollars = other.getDollars();
    cents = other.getCents();
    return *this; 
} 

ostream & operator<< (ostream & outStream, const Money & amount) {
    int absDollars = abs(amount.getDollars());
    int absCents = abs(amount.getCents());

    if (amount.getDollars() < 0 || amount.getDollars() < 0)
        outStream << "$-";
    else
        outStream << '$';
    outStream << absDollars;

    if (absCents >= 10)
        outStream << '.' << absCents;
    else
        outStream << '.' << '0' << absCents;
}

istream & operator>> (istream & inStream, Money & amount) {
    char dollarSign;
    inStream >> dollarSign; //hopefully

    if (dollarSign != '$') {
        cout << "No dollar sign in Money input.\n";
        exit(1);
    }
    else {
        double amountAsDouble;
        inStream >> amountAsDouble;
        amount.dollars = amount.dollarsPart(amountAsDouble);
        amount.cents = amount.centsPart(amountAsDouble);
    }
}

/* Use const quantifier to prevent these kind of stuff: (m1 + m2).input() */
const Money operator+ (const Money & amount1, const Money & amount2) {
    int allCents1 = amount1.getDollars() * 100 + amount1.getCents();
    int allCents2 = amount2.getDollars() * 100 + amount2.getCents();
    int sumAllCents = allCents1 + allCents2;
    int absAllCents = abs(sumAllCents);
    int finalDolars = absAllCents / 100;    
    int finalCents = absAllCents % 100;

    if (sumAllCents < 0) {
        finalDolars = -finalDolars;
        finalCents = -finalCents;
    }

    return Money(finalDolars, finalCents);
}

const Money operator- (const Money & amount1, const Money & amount2) {
    int allCents1 = amount1.getDollars() * 100 + amount1.getCents();
    int allCents2 = amount2.getDollars() * 100 + amount2.getCents();
    int diffAllCents = allCents1 - allCents2;
    int absAllCents = abs(diffAllCents);
    int finalDolars = absAllCents / 100;    
    int finalCents = absAllCents % 100;

    if (diffAllCents < 0) {
        finalDolars = -finalDolars;
        finalCents = -finalCents;
    }

    return Money(finalDolars, finalCents);
}

bool operator== (const Money & amount1, const Money & amount2) {
    return amount1.getDollars() == amount2.getDollars() && amount1.getCents()  == amount2.getCents();
}

bool operator!= (const Money & amount1, const Money & amount2) {
    //! By reference we can reach the private data
    return ! (amount1 == amount2);
}

const Money operator- (const Money & amount) {
    return Money(-amount.getDollars(), -amount.getCents());
}

inline double Money::getAmount () const {
    return dollars + cents * 0.01;
}

inline int Money::getDollars () const {
    return dollars;
}

inline int Money::getCents () const {
    return cents;
}

inline int Money::dollarsPart (double amount) const {
    return static_cast<int>(amount);
}

int Money::centsPart (double amount) const {
    double double_cents = amount * 100; 
    int int_cents = (round(fabs(double_cents))) % 100;

    if (amount < 0)
        int_cents = -int_cents;

    return int_cents;
}

inline int Money::round(double number) const {
    return static_cast<int>(floor(number + 0.5));
}