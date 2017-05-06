//
//  Surface_Designer.cpp
//  Evil_Gallows
//
//  Created by Benda Krisztián on 2017. 05. 04..
//  Copyright © 2017. Benda Krisztián. All rights reserved.
//

#include <iostream>

class Surface_Designer{
public:
    static void init_screen(){
        std::cout << "Hey! Welcome to the Evil Gallows game!\n";
        std::cout << "Lets start the game!\n";
        std::cout << " I've thought a word... or more HAHA\n";
        std::cout << " Please type a letter to guess my word(s)\n\n";
        
    }
    
    static void reply(bool guess, std::string rightguesses, std::string wrongguesses){
        clean_screen();
        if (guess)
            reply_goodguess();
        else reply_wrongguees();
        std::cout << "Your word: " << rightguesses << std::endl;
        std::cout << "Wrong guess(es): " << wrongguesses << std::endl;
        draw_gallows(wrongguesses);
    }
    
    static void draw_win(){
        std::cout << "NOOOO! You won! Congratulations!\n";
    }
private:
    static void reply_goodguess(){
        std::cout << "ARRRGHHH! Your guess was good. You have one more chance...\n";
    }
    static void reply_wrongguees(){
        std::cout << "HAHA! WRONG guess! You are going to die!!!\n";
    }
    
    static void clean_screen(){
        std::cout << std::string(50, '\n');
    }
    

//    _____
//    |/  |
//    |   O
//    |  /|\
//    |  / \
//    |
//   ________
//  /        \
    
    static void draw_gallows(std::string wrong){
        int tips = int(wrong.size() / 2);
        std::cout << std::endl;
        if (tips > 2)
            std::cout << "  _____";
        std::cout << std::endl;
        if (tips > 3)
            std::cout << "  |/  |";
        else if(tips > 1)
            std::cout << "  |/";
        std::cout << "\n";
        if (tips > 4)
            std::cout << "  |   O";
        else if (tips > 1)
            std::cout << "  |";
        std::cout << "\n";
        if (tips > 1){
            std::cout << "  |  ";
            if (tips > 6)
                std::cout << "/";
            if (tips == 6)
                std::cout << " ";
            if (tips > 5)
                std::cout << "|";
            if (tips > 7)
                std::cout << "\\";
        }
        std::cout << "\n";
        if (tips > 1){
            std::cout << "  |  ";
            if (tips > 8)
                std::cout << "/ ";
            if (tips > 9)
                std::cout << "\\";
        }
        std::cout << "\n";
        if (tips > 1)
            std::cout << "  |";
        std::cout << "\n";
        if (tips > 0){
            std::cout << " ________\n";
            std::cout << "/        \\";
        }
        std::cout << "\n\n";
        if (tips > 9)
            std::cout << "HAHAHA! I won! You're dead!\n";
    }
};
