//
// Created by ilong on 2020/3/17.
//

#ifndef EFFECTIVE_C_CTEXTBLOCK_H
#define EFFECTIVE_C_CTEXTBLOCK_H

class CTextBlock final{
public:
    CTextBlock(char * text){
        pText = text;
    }
    char& operator[](std::size_t position) const {
        return pText[position];
    }

private:
    char * pText;
};


#endif //EFFECTIVE_C_CTEXTBLOCK_H
