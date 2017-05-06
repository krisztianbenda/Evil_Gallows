//
//  Gallows.cpp
//  Evil_Gallows
//
//  Created by Benda Krisztián on 2017. 05. 02..
//  Copyright © 2017. Benda Krisztián. All rights reserved.
//
/*
 _____
 |/  |
 |   O
 |  /|\
 |  / \
 |
________
*/
#include "Gallows.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <regex>
#include <set>

Gallows::Gallows(std::string filename){
    read_data(filename);
}

void Gallows::play(){
    sd.init_screen();
    char tip;
    while (!win && !lose &&std::cin >> tip){
        //Megvizsgaljuk, hogy volt e mar ez a tipp
        bool guess_again = guesses_contain_tip(tip);
        //Ha egy olyan tippet adott a jatokes,
        // amit mar egyszer sikeresen tippelt, akkor ez egy rossztippnek szamit
        if(guess_again)
            wrongguesses.insert(tip);
        else{
            evaluate_tip(tip);
            choose_fitting_words(tip);
        }
        sd.reply(goodguess, get_right_word_printformat(), get_wrong_letters());
        clean_variables();
        check_win();
        check_lose();
        guess_again = false;
    }
    if (win)
        sd.draw_win();
    
}


//egy fajlbol beolvassa a szavakat
void Gallows::read_data(std::string filename){
    std::ifstream myfile(filename);
    std::string line;
    if (myfile.is_open()){
        while ( getline(myfile,line) ){
            word w;
            w.text = line;
            for(int i = 0; i < line.length(); ++i)
                w.let_tipped.push_back(false);
            dictionary.push_back(w);
        }
        myfile.close();
    }
}
    
// Az a legjobb formula, amelyikre a legtobb szo illik
//  a tobbi formula torolheto. Ezert fele a fuggveny
formula Gallows::get_best_formula(){
    std::sort(forms.begin(), forms.end(), [](formula a, formula b){return a.count >= b.count;});
    forms.erase(++forms.begin(), forms.end());
    return forms.front();
}
    
//toroljuk a formulara nem illo szavakat a szotarbol
void Gallows::remove_inappropirate_words(formula form){
    auto new_end_of_words = std::remove_if(dictionary.begin(), dictionary.end(),
                                           [form](word w){
                                               return !std::regex_match(w.text, std::regex(form.regex));
                                           });
    dictionary.erase(new_end_of_words, dictionary.end());
}
    
//Kivalasztjuk azokat a szavakat amelyek a legjobb
// formulara illenek, es a tobbit elhagyjuk.
//Ez alapjan tortenik a jo, vagy rossz tipp eldontese is
void Gallows::choose_fitting_words(const char& tip){
    auto choosed_form = get_best_formula();
    if (choosed_form.stricter){
        //Jo a tipp, ha formula szigorubb, mint eddig
        // ekkor a jol tippelt betuket megjeloljuk a szavakban is
        goodguess = true;
        rightguesses.insert(tip);
        std::for_each(dictionary.begin(), dictionary.end(),
                      [tip](word& word_){
                          for (int i = 0; i < word_.text.length(); ++i){
                              if (word_.text[i] == tip)
                                  word_.let_tipped[i] = true;
                          }
                      });
    }
    if (!goodguess)
        wrongguesses.insert(tip);
    remove_inappropirate_words(choosed_form);
}
    
// regularis kifejezest epit az a megadott szohoz a megadott betuvel
formula Gallows::build_regex(const word& word_, const char & letter){
    formula form;
    std::for_each(word_.text.begin(), word_.text.end(),
        [&form, letter](char let){
            if (let == letter){
                form.regex += letter;
                form.stricter = true;
            } else
                form.regex += std::string("[^") + letter + "]";
        }
    );
    return form;
}
    
// A szotar szavaiban lecsekkolja a @form-ban tarolt regexre illo szavakat,
//  a formhoz szamolja, hany szot talalt
formula Gallows::check_regex_in_words(formula form){
    for (auto & word : dictionary){
        if (std::regex_match(word.text, std::regex(form.regex))){
            form.count++;
            word.is_tested = true;
        }
    }
    return form;
}
    
// kiertekeljuk a tippet es regrularis kifejezeseket
// (formula-kat) keszitunk a szavakra
void Gallows::evaluate_tip(const char& letter){
    for (auto word : dictionary){
        if (!word.is_tested){
            formula form = build_regex(word, letter);
            form = check_regex_in_words(form);
            forms.push_back(form);
        }
    }
}
    
//Visszaadja a tippelendo szot kiirando formaban
std::string Gallows::get_right_word_printformat(){
    std::string right;
    right = std::string(dictionary.front().text.length(), '_');
    for (int i = 0; i < dictionary.front().text.length();++i)
        if (dictionary.front().let_tipped[i])
            right[i] = dictionary.front().text[i];
    return right;
}
    
//Visszaadja a rosszul tippelt betuket formazva
std::string Gallows::get_wrong_letters(){
    std::string wrong;
    for (auto & guess : wrongguesses)
        wrong += (guess + std::string(" "));
    return wrong;
}

// Kitorli a regexeket, visszaaliitja a szavakat eredeti formaba
void Gallows::clean_variables(){
    forms.erase(forms.begin(), forms.end());
    std::for_each(dictionary.begin(), dictionary.end(), [](word& w){w.is_tested=false;});
    goodguess = false;
}
    
void Gallows::check_win(){
    if (dictionary.size() == 1){
        win = true;
        for (auto tipped : dictionary.front().let_tipped)
            win = win & tipped;
    }
}
    
void Gallows::check_lose(){
    if (wrongguesses.size() > 10)
        lose = true;
}
    
// Igazzal ter vissza ha a jelenlegi tipp, mar elofordult egyszer
bool Gallows::guesses_contain_tip(const char& tip){
    return (rightguesses.find(tip) != rightguesses.end()) ||
        (wrongguesses.find(tip) != wrongguesses.end());
}


