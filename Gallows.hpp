//
//  Gallows.hpp
//  Evil_Gallows
//
//  Created by Benda Krisztián on 2017. 05. 02..
//  Copyright © 2017. Benda Krisztián. All rights reserved.
//

#ifndef Gallows_hpp
#define Gallows_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "Surface_Designer.cpp"
#include <set>

// A beolvasott szavak tarolasahoz kello struktura
//  @let_tipped: a szo minden betujehez letaroljuk,
//   hogy az adott betut tippeltek-e mar
//  @is_tested: A feldolgozas soran nyomonkovetjuk,
//   hogy megvizsgaltuk-e mar az objektumot
struct word{
    std::string text;
    std::vector<bool> let_tipped;
    bool is_tested = false;
};

// A szavak es a tippelesek egyezoseget regularis kifejezesekkel
// vizsgaljuk. Ehhez kell a @formula struktura
//  @count: a @regex-nek eleget tevo szavak szama
//  @stricter: Ha a tipp jo volt, akkor a regexp egyre 'szigorubb' lesz
//   a @stricter valtozon keresztul tudjuk ezt nyomon kovetni
struct formula{
    std::string regex = "";
    unsigned int count = 0;
    bool stricter = false;
};

//Akasztofa osztaly
class Gallows{
public:
    Gallows(std::string);
    Gallows(const Gallows&) = delete;
    void operator=  (const Gallows&) = delete;
    ~Gallows() = default;
    // A jatek futasat vezerlo fuggveny
    void play();
    
private:
    // A Surface_Designer felel a kirajzolasaert
    // @dictionary: a szavak tara, amelyik a jatek eloremenetelevel csokken
    // @forms: a regexek kezelesehez
    // @goodguess: jatekos tippjenek aktualis erteke
    // @wrongguesses: az eddigi rossz tippek halmaza
    // @rightguesses: a jo tippek halamza
    // @win, @lose: nyereseg-veszteseg
    Surface_Designer sd;
    std::vector<word> dictionary;
    std::vector<formula> forms;
    bool goodguess = false;
    std::set<char> wrongguesses;
    std::set<char> rightguesses;
    bool win = false, lose = false;
    
    void read_data(std::string);
    
    formula get_best_formula();
    
    void remove_inappropirate_words(formula);
    
    void choose_fitting_words(const char&);
    
    formula build_regex(const word&, const char&);
    
    formula check_regex_in_words(formula);
    
    void evaluate_tip(const char&);
    
    std::string get_right_word_printformat();
    
    std::string get_wrong_letters();
    
    void clean_variables();
    
    void check_win();
    
    void check_lose();
    
    bool guesses_contain_tip(const char&);
};

#endif /* Gallows_hpp */
