#include <iostream>
#include <fstream>
using namespace std;


//mychar.h
class MyChar
{
private:
	char character;

public:
	MyChar(char a = '\0');
	MyChar(const MyChar&);
	void operator=(const MyChar&);
	bool operator==(const MyChar&);
	bool operator!=(const MyChar&);

	char getCharacter()const { return character; }
	void setCharacter(char a) { character = a; }

	char readchar(istream& inp);
	char readfilechar(ifstream& fin);
};

void operator +(MyChar& c);
void operator -(MyChar& c);

void operator +(MyChar& c, int& key);
void operator -(MyChar& c, int& key);

//mychar.cpp


MyChar::MyChar(char a) {
	character = a;
}
MyChar::MyChar(const MyChar& other) {
	character = other.character;
}
void MyChar::operator=(const MyChar& other) {
	this->setCharacter(other.getCharacter());
}
bool MyChar::operator==(const MyChar& other) {
	if (this->getCharacter() == other.getCharacter())
		return true;
	return false;
}
bool MyChar::operator!=(const MyChar& other) {
	if (this->getCharacter() != other.getCharacter())
		return true;
	return false;
}
char MyChar::readchar(istream& inp) {
	inp >> character;
	return character;
}

char MyChar::readfilechar(ifstream& fin) {
	fin >> character;
	return character;
}

void operator +(MyChar& c) {
	if (c.getCharacter() >= 'a' && c.getCharacter() <= 'z')
		c.setCharacter(c.getCharacter() - 32);
}

void operator -(MyChar& c) {
	if (c.getCharacter() >= 'A' && c.getCharacter() <= 'Z')
		c.setCharacter(c.getCharacter() + 32);
}

void operator +(MyChar& c, int& key) {
	if (key >= 26) {
		key = key % 26;
	}
	//key = key + c.character;
	if (c.getCharacter() >= 'a' && c.getCharacter() <= 'z')
	{
		if (key + c.getCharacter() > 'z') {
			c.setCharacter('a' + (key - ('z' - c.getCharacter())));
		}
		else
		{
			c.setCharacter(c.getCharacter() + key);
		}
	}
	else
	{
		if (key + c.getCharacter() > 'Z') {
			c.setCharacter('A' + (key - ('Z' - c.getCharacter())));
		}
		else
		{
			c.setCharacter(c.getCharacter() + key);
		}
	}
}

void operator -(MyChar& c, int& key) {
	if (key > 26) {
		key = key % 26;
	}
	//key = key + c.character;
	if (c.getCharacter() >= 'a' && c.getCharacter() <= 'z')
	{
		if (c.getCharacter() - key < 'a') {
			c.setCharacter('z' - (key - (c.getCharacter() - 'a')));
		}
		else
		{
			c.setCharacter(c.getCharacter() - key);
		}

	}
	else
	{
		if (c.getCharacter() - key < 'A') {
			c.setCharacter('Z' - (key - (c.getCharacter() - 'A')));
		}
		else
		{
			c.setCharacter(c.getCharacter() - key);
		}
	}
}


//next file 
//word.h

MyChar* deepword(MyChar* other, int othersize);
class Word
{
private:
	MyChar* word;
	int size;
	int code;
	MyChar* tempcode;
	int newsize;
public:
	Word(MyChar* a = nullptr, int s = 0);
	Word(const Word&);

	MyChar* getarray()const { return word; }
	int getsize()const { return size; }
	MyChar* gettempcode()const { return tempcode; }
	int getcode()const { return code; }
	int getnewsize() const { return newsize; }
	//  int gettotal()const{ return total;}

	void setnewsize(int s) { newsize = s; }
	void setarray(MyChar* p) { word = deepword(p, size); };
	void setsize(int s) { size = s; }
	void settempcode(MyChar* p) { tempcode = deepword(p, size); }		//
	void setcode(int s) { code = s; }		//
   // void settotal(int s){ total = s;}

	void regrow(int size);

	char readword(istream& inp);
	char readfileword(ifstream& fin);

	void writeWord(ofstream& fout);
	void operator=(const Word&);
	Word operator+(const Word&);
	bool operator==(const Word&);
	bool operator!=(const Word&);
	void spellcheck();
};

ostream& operator<<(ostream& out, Word& w);

void operator +(Word& w);
void operator -(Word& w);

void operator +(Word& w, int& key);
void operator -(Word& w, int& key);

void operator !(Word& w);
void operator --(Word& w);


//word.cpp

MyChar* deepword(MyChar* other, int othersize) {
    MyChar* temp = new MyChar[othersize];
    for (int i = 0; i < othersize; i++) {
        temp[i] = other[i];
    }
    return temp;
}

Word::Word(MyChar* a, int s) {
    word = a;
    size = s;
    code = 0;
    newsize = 1;
    tempcode = new MyChar[newsize];
    //total = t;
}
Word::Word(const Word& other) {
    word = deepword(other.word, other.size);
    size = other.size;
    code = other.code;
    tempcode = other.tempcode;
    //total = other.total;
}

void Word::operator=(const Word& other) {
    word = deepword(other.word, other.size);
    size = other.size;
    //total = other.total;
}
bool Word::operator==(const Word& other) {
    if (this->getsize() == other.getsize())
    {
        for (int i = 0; i < this->getsize(); i++) {
            if (this->getarray()[i] != other.getarray()[i])
                return false;
        }
    }
    else
        return false;
    return true;
}
bool Word::operator!=(const Word& other) {
    if (this->getsize() == other.getsize())
    {
        for (int i = 0; i < this->getsize(); i++) {
            if (this->getarray()[i] != other.getarray()[i])
                return true;
        }
    }
    else
        return true;
    return false;
}

Word Word::operator+(const Word& other) {
    Word temp;
    int s = this->size + other.size;
    MyChar* tem = new MyChar[s];
    temp.setsize(s);
    for (int i = 0; i < this->size; i++) {
        tem[i] = this->getarray()[i];
    }
    int index = 0;
    for (int i = this->getsize(); i < s; i++) {
        tem[i] = other.getarray()[index];
        index++;
    }
    temp.setarray(tem);
    return temp;
}

void Word::regrow(int size) {
    MyChar* temp = new MyChar[size];

    for (int i = 0; i < getsize(); i++)
        temp[i] = getarray()[i];

    delete[] getarray();
    setsize(size);
    setarray(temp);
}

char Word::readword(istream& inp) {
    char temp;
    do {
        regrow(getsize() + 1);
        temp = word[getsize() - 1].readchar(inp);
        //settotal(gettotal()+1);
        setcode(getcode() + temp);  //ascii value of temp added to code

    } while ((temp > 64 && temp < 91) || (temp > 96 && temp < 123));
    regrow(getsize() - 1);
    gettempcode()[0].setCharacter(getcode() % 10 + 48);  //generating final code and storing at tempcode[0] array;
    //settotal(gettotal()-1);

    return temp;
}

ostream& operator<<(ostream& out, Word& w) {
    for (int i = 0; i < w.getsize(); i++) {
        out << w.getarray()[i].getCharacter();
    }
    return out;
}

char Word::readfileword(ifstream& fin) {
    char temp;
    do {
        regrow(getsize() + 1);
        temp = word[getsize() - 1].readfilechar(fin);
        //settotal(gettotal()+1);
        //setcode(getcode()+temp);  //ascii value of temp added to code


    } while ((temp > 64 && temp < 91) || (temp > 96 && temp < 123));
    regrow(getsize() - 1);
    //gettempcode()[0].setCharacter(getcode()%10 + 48); //generating final code and storing at tempcode[0] array;

    return temp;
}

void Word::spellcheck() {
    int s = this->getsize();
    char* temp = new char[s];
    for (int i = 0; i < s; i++) {
        temp[i] = this->getarray()[i].getCharacter();
    }
    temp[s] = '\0';

    char word[100];
    bool check = false;
    ifstream fin;
    ofstream fout;
    fin.open("dictionary.txt");
    fout.open("newdic.txt", ios::app);
    while (!fin.eof())
    {
        fin >> word;
        if (strcmp(word, temp) == 0) {
            check = true;
        }
        if (check == true) {
            break;
        }
    }
    if (check == false) {
        fout << temp << endl;
        check = false;
    }
}

void Word::writeWord(ofstream& fout) {
    for (int i = 0; i < getsize(); i++)
        fout << getarray()[i].getCharacter();
}



void operator +(Word& w) {
    for (int i = 0; i < w.getsize(); i++)
        + w.getarray()[i];
}

void operator -(Word& w) {
    for (int i = 0; i < w.getsize(); i++)
        - w.getarray()[i];
}

void operator +(Word& w, int& key) {
    for (int i = 0; i < w.getsize(); i++)
        operator+(w.getarray()[i], key);
}

void operator -(Word& w, int& key) {
    for (int i = 0; i < w.getsize(); i++)
        w.getarray()[i] - key;
}

void operator !(Word& w) {
    int s = w.getsize();
    int stemp = 0;
    char tem;
    for (int i = 0; i < s; i++) {
        tem = w.getarray()[i].getCharacter();
        w.setcode(tem + w.getcode());
    }
    w.gettempcode()[0].setCharacter((w.getcode() % 65 % 10) + 48); //generating final code and storing at tempcode[0] array;


    MyChar* temp = w.gettempcode();
    w.settempcode(w.getarray());
    w.setnewsize(w.getsize());
    w.setsize(1);
    w.setarray(temp);
}


void operator --(Word& w) {

    MyChar* temp = w.gettempcode();
    w.settempcode(w.getarray());
    //w.setnewsize(w.getsize());
    w.setsize(w.getnewsize());
    w.setnewsize(1);
    w.setarray(temp);
    //MyChar* temp = w.gettempcode();
    //w.settempcode(w.getarray());
    //w.setarray(temp);
}

//sentence.h

Word* deepsentence(Word* other, int sizew);

class Sentence
{
private:
    Word* sentence;
    int size;

public:
    Sentence(Word* w = nullptr, int s = 0);
    Sentence(const Sentence&);

    Word* getarray()const { return sentence; }
    int getsize()const { return size; }

    void setarray(Word* p) { sentence = deepsentence(p, size); }
    void setsize(int s) { size = s; }

    void regrow(int size);

    char readsentence(istream& inp);
    char readfilesentence(ifstream& fin);

    void writeSentence(ofstream& fout);
    void operator=(const Sentence&);
    Sentence operator+(const Sentence&);
    bool operator==(const Sentence&);
    bool operator!=(const Sentence&);
    void spellcheck();
};

ostream& operator<<(ostream& out, Sentence& s);

void operator +(Sentence& s);
void operator -(Sentence& s);

void operator +(Sentence& s, int& key);
void operator -(Sentence& s, int& key);

void operator !(Sentence& s);
void operator --(Sentence& s);

//sentence.cpp

Word* deepsentence(Word* other, int sizew) {
    Word* temp = new Word[sizew];
    for (int i = 0; i < sizew; i++) {
        temp[i].setsize(other[i].getsize());
        temp[i].setarray(other[i].getarray());
    }
    return temp;
}

Sentence::Sentence(Word* w, int s) {
    sentence = w;
    size = s;
}

Sentence::Sentence(const Sentence& other) {
    size = other.size;
    sentence = deepsentence(other.sentence, other.size);
}
void Sentence::operator=(const Sentence& other) {
    size = other.size;
    sentence = deepsentence(other.sentence, other.size);
}
Sentence Sentence::operator+(const Sentence& other) {
    int s = this->getsize() + other.getsize();
    Sentence temp;
    temp.setsize(s);
    Word* tem = new Word[s];

    for (int i = 0; i < this->size; i++) {
        tem[i] = this->getarray()[i];
    }
    int index = 0;
    for (int i = this->getsize(); i < s; i++) {
        tem[i] = other.getarray()[index];
        index++;
    }
    temp.setarray(tem);
    return temp;
}
bool Sentence::operator==(const Sentence& other) {
    if (this->getsize() == other.getsize())
    {
        for (int i = 0; i < this->getsize(); i++) {
            if (this->getarray()[i] != other.getarray()[i])
                return false;
        }
    }
    else
        return false;
    return true;
}
bool Sentence::operator!=(const Sentence& other) {
    if (this->getsize() == other.getsize())
    {
        for (int i = 0; i < this->getsize(); i++) {
            if (this->getarray()[i] != other.getarray()[i])
                return true;
        }
    }
    else
        return true;
    return false;
}
void Sentence::spellcheck() {
    int s = this->getsize();
    for (int i = 0; i < this->getsize(); i++) {
        getarray()[i].spellcheck();
    }
}
void Sentence::regrow(int size) {
    Word* temp = new Word[size];

    for (int i = 0; i < getsize(); i++)
        temp[i] = getarray()[i];

    delete[] getarray();
    setsize(size);
    setarray(temp);
}

char Sentence::readsentence(istream& inp) {
    char temp;
    do {
        regrow(getsize() + 1);
        temp = sentence[getsize() - 1].readword(inp);

    } while (temp != '.');

    inp >> temp;
    return temp;
}

ostream& operator<<(ostream& out, Sentence& s) {
    for (int i = 0; i < s.getsize() - 1; i++) {
        out << s.getarray()[i] << ' ';
    }
    out << s.getarray()[s.getsize() - 1] << ". ";
    return out;
}

char Sentence::readfilesentence(ifstream& fin) {
    char temp;
    do {
        regrow(getsize() + 1);
        temp = sentence[getsize() - 1].readfileword(fin);

    } while (temp != '.');

    fin >> temp;
    return temp;
}

void Sentence::writeSentence(ofstream& fout) {
    for (int i = 0; i < getsize() - 1; i++) {
        getarray()[i].writeWord(fout);
        fout << ' ';
    }
    getarray()[getsize() - 1].writeWord(fout);
    fout << ". ";
}

void operator +(Sentence& s) {
    for (int i = 0; i < s.getsize(); i++)
        + s.getarray()[i];
}

void operator -(Sentence& s) {
    for (int i = 0; i < s.getsize(); i++)
        - s.getarray()[i];
}

void operator +(Sentence& s, int& key) {
    for (int i = 0; i < s.getsize(); i++)
        operator+(s.getarray()[i], key);
}

void operator -(Sentence& s, int& key) {
    for (int i = 0; i < s.getsize(); i++)
        s.getarray()[i] - key;
}

void operator !(Sentence& s) {
    for (int i = 0; i < s.getsize(); i++) {
        !s.getarray()[i];
    }
}

void operator --(Sentence& s) {
    for (int i = 0; i < s.getsize(); i++) {
        --s.getarray()[i];
    }
}

//paragraph.h

Sentence* deepparagraph(Sentence* other, int sizep);

class Paragraph
{
private:
    Sentence* paragraph;
    int size;

public:
    Paragraph(Sentence* sen = nullptr, int s = 0);
    Paragraph(const Paragraph&);

    Sentence* getarray()const { return paragraph; }
    int getsize()const { return size; }

    void setarray(Sentence* p) { paragraph = deepparagraph(p, size); }
    void setsize(int s) { size = s; }

    void regrow(int size);

    char readparagraph(istream& inp);
    char readfileparagraph(ifstream& fin);

    void writeParagraph(ofstream& fout);
    void operator=(const Paragraph&);
    Paragraph operator+(const Paragraph&);
    bool operator==(const Paragraph&);
    bool operator!=(const Paragraph&);
    void spellcheck();
};

ostream& operator <<(ostream& out, Paragraph& p);

void operator +(Paragraph& p);
void operator -(Paragraph& p);

void operator +(Paragraph& p, int& key);
void operator -(Paragraph& p, int& key);

void operator !(Paragraph& p);
void operator --(Paragraph& p);

//paragraph.cpp

Sentence* deepparagraph(Sentence* other, int sizep) {
    Sentence* temp = new Sentence[sizep];
    for (int i = 0; i < sizep; i++) {
        temp[i].setsize(other[i].getsize());
        temp[i].setarray(other[i].getarray());
    }
    return temp;
}

Paragraph::Paragraph(Sentence* sen, int s) {
    paragraph = sen;
    size = s;
}

Paragraph::Paragraph(const Paragraph& other) {
    size = other.size;
    paragraph = deepparagraph(other.paragraph, other.size);
}
void Paragraph::operator=(const Paragraph& other) {
    size = other.size;
    paragraph = deepparagraph(other.paragraph, other.size);
}
Paragraph Paragraph::operator+(const Paragraph& other) {
    int s = this->getsize() + other.getsize();
    Paragraph temp;
    temp.setsize(s);
    Sentence* tem = new Sentence[s];

    for (int i = 0; i < this->size; i++) {
        tem[i] = this->getarray()[i];
    }
    int index = 0;
    for (int i = this->getsize(); i < s; i++) {
        tem[i] = other.getarray()[index];
        index++;
    }
    temp.setarray(tem);
    return temp;
}
bool Paragraph::operator==(const Paragraph& other) {
    if (this->getsize() == other.getsize())
    {
        for (int i = 0; i < this->getsize(); i++) {
            if (this->getarray()[i] != other.getarray()[i])
                return false;
        }
    }
    else
        return false;
    return true;
}
bool Paragraph::operator!=(const Paragraph& other) {
    if (this->getsize() == other.getsize())
    {
        for (int i = 0; i < this->getsize(); i++) {
            if (this->getarray()[i] != other.getarray()[i])
                return true;
        }
    }
    else
        return true;
    return false;
}

void Paragraph::regrow(int size) {
    Sentence* temp = new Sentence[size];

    for (int i = 0; i < getsize(); i++)
        temp[i] = getarray()[i];

    delete[] getarray();
    setsize(size);
    setarray(temp);
}

char Paragraph::readparagraph(istream& inp) {
    char temp;
    do {
        regrow(getsize() + 1);
        temp = paragraph[getsize() - 1].readsentence(inp);

    } while (temp != '$');

    inp >> temp;
    return temp;
}

ostream& operator <<(ostream& out, Paragraph& p) {
    for (int i = 0; i < p.getsize(); i++) {
        out << p.getarray()[i];
    }
    return out;
}

char Paragraph::readfileparagraph(ifstream& fin) {
    char temp;
    do {
        regrow(getsize() + 1);
        temp = paragraph[getsize() - 1].readfilesentence(fin);

    } while (temp != '$');

    if (fin >> temp)
        return temp;
    return '\0';
}

void Paragraph::writeParagraph(ofstream& fout) {
    for (int i = 0; i < getsize(); i++) {
        getarray()[i].writeSentence(fout);
    }
}
void Paragraph::spellcheck() {
    int s = this->getsize();
    for (int i = 0; i < this->getsize(); i++) {
        getarray()[i].spellcheck();
    }
}

void operator +(Paragraph& p) {
    for (int i = 0; i < p.getsize(); i++)
        + p.getarray()[i];
}

void operator -(Paragraph& p) {
    for (int i = 0; i < p.getsize(); i++)
        - p.getarray()[i];
}

void operator +(Paragraph& p, int& key) {
    for (int i = 0; i < p.getsize(); i++)
        operator+(p.getarray()[i], key);
}

void operator -(Paragraph& p, int& key) {
    for (int i = 0; i < p.getsize(); i++)
        p.getarray()[i] - key;
}

void operator !(Paragraph& p) {
    for (int i = 0; i < p.getsize(); i++) {
        !p.getarray()[i];
    }
}

void operator --(Paragraph& p) {
    for (int i = 0; i < p.getsize(); i++) {
        --p.getarray()[i];
    }
}

//chapter.h

Paragraph* deepchapter(Paragraph* other, int sizec);

class Chapter
{
private:
    Paragraph* chapter;
    int size;
    bool isUpper;
    bool isLower;
    bool isEncrypt;
    bool isDecrypt;
    bool isCompress;
    bool isDecompress;

public:
    Chapter(bool a = false, bool b = false, bool c = false, bool d = false, bool e = false, bool f = false, int s = 0, Paragraph* p = nullptr);
    Chapter(const Chapter&);

    Paragraph* getarray()const { return chapter; }
    int getsize()const { return size; }
    bool getUpper()const { return isUpper; }
    bool getLower()const { return isLower; }
    bool getEncrypt()const { return isEncrypt; }
    bool getDecrypt()const { return isDecrypt; }
    bool getCompress()const { return isCompress; }
    bool getDecompress()const { return isDecompress; }

    void setarray(Paragraph* p) { chapter = deepchapter(p, size); }
    void setsize(int s) { size = s; }
    void setUpper(bool b) { isUpper = b; }
    void setLower(bool b) { isLower = b; }
    void setEncrypt(bool b) { isEncrypt = b; }
    void setDecrypt(bool b) { isDecrypt = b; }
    void setCompress(bool b) { isCompress = b; }
    void setDecompress(bool b) { isDecompress = b; }

    void regrow(int size);
    void frequencyData(ofstream& fout);
    int totalcharacters();
    void operator=(const Chapter&);
    Chapter operator+(const Chapter&);
    bool operator==(const Chapter&);
    bool operator!=(const Chapter&);
    void spellcheck();
};

istream& operator >>(istream& inp, Chapter& ch);
ostream& operator <<(ostream& out, Chapter& ch);

ifstream& operator >>(ifstream& fin, Chapter& ch);
ofstream& operator <<(ofstream& fout, Chapter& ch);

void operator +(Chapter& ch);
void operator -(Chapter& ch);

void operator +(Chapter& ch, int& key);
void operator -(Chapter& ch, int& key);

void operator !(Chapter& ch);
void operator --(Chapter& ch);

//chapter.cpp

Paragraph* deepchapter(Paragraph* other, int sizec) {
    Paragraph* temp = new Paragraph[sizec];
    for (int i = 0; i < sizec; i++) {
        temp[i].setsize(other[i].getsize());
        temp[i].setarray(other[i].getarray());
    }
    return temp;
}

Chapter::Chapter(bool a, bool b, bool c, bool d, bool e, bool f, int s, Paragraph* p) {
    isUpper = a;
    isLower = b;
    isEncrypt = c;
    isDecrypt = d;
    isCompress = e;
    isDecompress = f;
    size = s;
    chapter = p;
}

Chapter::Chapter(const Chapter& other) {
    isUpper = other.isUpper;
    isLower = other.isLower;
    isEncrypt = other.isEncrypt;
    isDecrypt = other.isDecrypt;
    isCompress = other.isCompress;
    isDecompress = other.isDecompress;
    size = other.size;
    chapter = deepchapter(other.chapter, other.size);
}
void Chapter::operator=(const Chapter& other) {
    isUpper = other.isUpper;
    isLower = other.isLower;
    isEncrypt = other.isEncrypt;
    isDecrypt = other.isDecrypt;
    isCompress = other.isCompress;
    isDecompress = other.isDecompress;
    size = other.size;
    chapter = deepchapter(other.chapter, other.size);
}

Chapter Chapter::operator+(const Chapter& other) {
    int s = this->size + other.size;
    Chapter temp;
    temp.setsize(s);
    Paragraph* tem = new Paragraph[s];

    for (int i = 0; i < this->size; i++) {
        tem[i] = this->getarray()[i];
    }
    int index = 0;
    for (int i = this->getsize(); i < s; i++) {
        tem[i] = other.getarray()[index];
        index++;
    }
    temp.setarray(tem);
    return temp;
}
bool Chapter::operator==(const Chapter& other) {
    if (this->getsize() == other.getsize())
    {
        for (int i = 0; i < this->getsize(); i++) {
            if (this->getarray()[i] != other.getarray()[i])
                return false;
        }
    }
    else
        return false;
    return true;
}
bool Chapter::operator!=(const Chapter& other) {
    if (this->getsize() == other.getsize())
    {
        for (int i = 0; i < this->getsize(); i++) {
            if (this->getarray()[i] != other.getarray()[i])
                return true;
        }
    }
    else
        return true;
    return false;
}

void Chapter::regrow(int size) {
    Paragraph* temp = new Paragraph[size];

    for (int i = 0; i < getsize(); i++)
        temp[i] = getarray()[i];

    delete[] getarray();
    setsize(size);
    setarray(temp);
}

void Chapter::frequencyData(ofstream& fout) {

    for (int i = 0; i < getsize(); i++) {
        fout << "Paragraph number: " << i + 1 << endl;
        fout << "Sentences in Paragraph " << i + 1 << ": " << getarray()[i].getsize() << endl;

        for (int j = 0; j < getarray()[i].getsize(); j++)
        {
            fout << "Words in Sentence no. " << j + 1 << ": " << getarray()[i].getarray()[j].getsize() << endl;

            for (int k = 0; k < getarray()[i].getarray()[j].getsize(); k++)
            {
                fout << "Characters in Word no. " << k + 1 << " in Sentence no. " << j + 1 << ": " << getarray()[i].getarray()[j].getarray()[k].getsize() << endl;
            }
        }
    }
}

int Chapter::totalcharacters() {
    int count = 0;
    for (int i = 0; i < getsize(); i++) {
        for (int j = 0; j < getarray()[i].getsize(); j++)
        {
            for (int k = 0; k < getarray()[i].getarray()[j].getsize(); k++)
            {
                count = count + getarray()[i].getarray()[j].getarray()[k].getsize();
            }
        }
    }
    return count;
}

void Chapter::spellcheck() {
    int s = this->getsize();
    for (int i = 0; i < this->getsize(); i++) {
        getarray()[i].spellcheck();
    }
}

istream& operator >>(istream& inp, Chapter& ch) {
    char temp;
    inp >> noskipws;
    do {
        ch.regrow(ch.getsize() + 1);
        temp = ch.getarray()[ch.getsize() - 1].readparagraph(inp);

    } while (temp != '\n');

    return inp;
}

ostream& operator <<(ostream& out, Chapter& ch) {
    if (ch.getsize() > 0) {
        for (int i = 0; i < ch.getsize() - 1; i++) {
            out << ch.getarray()[i] << "\n\n";
        }
        out << ch.getarray()[ch.getsize() - 1];
        return out;
    }
    else
        return out << " No TEXT Found!.\n";
}

ifstream& operator >>(ifstream& fin, Chapter& ch) {
    char temp;
    fin >> noskipws;
    do {
        ch.regrow(ch.getsize() + 1);
        temp = ch.getarray()[ch.getsize() - 1].readfileparagraph(fin);

    } while (temp != '\0');
    return fin;
}

ofstream& operator <<(ofstream& fout, Chapter& ch) {
    for (int i = 0; i < ch.getsize() - 1; i++) {
        ch.getarray()[i].writeParagraph(fout);
        fout << "\n\n";
    }
    ch.getarray()[ch.getsize() - 1].writeParagraph(fout);
    return fout;
}

void operator +(Chapter& ch) {
    if (ch.getsize() > 0) {
        if (ch.getUpper() == false) {
            for (int i = 0; i < ch.getsize(); i++)
                + ch.getarray()[i];
            ch.setUpper(true);
            ch.setLower(false);
        }
        else
            cout << " Text Already in UpperCase.\n";
    }
    else
        cout << " No TEXT.\n";
}

void operator -(Chapter& ch) {
    if (ch.getsize() > 0) {
        if (ch.getLower() == false) {
            for (int i = 0; i < ch.getsize(); i++)
                - ch.getarray()[i];
            ch.setLower(true);
            ch.setUpper(false);
        }
        else
            cout << " Text Already in LowerCase.\n";
    }
    else
        cout << " No TEXT.\n";
}

void operator +(Chapter& ch, int& key) {
    if (ch.getsize() > 0) {
        if (ch.getEncrypt() == false) {
            for (int i = 0; i < ch.getsize(); i++)
                operator+(ch.getarray()[i], key);
            ch.setEncrypt(true);
            ch.setDecrypt(false);
        }
        else
            cout << " Text Already Encrypted.\n";
    }
    else
        cout << " No TEXT.\n";
}

void operator -(Chapter& ch, int& key) {
    if (ch.getsize() > 0) {
        if (ch.getDecrypt() == false) {
            for (int i = 0; i < ch.getsize(); i++)
                ch.getarray()[i] - key;

            ch.setDecrypt(true);
            ch.setEncrypt(false);
        }
        else
            cout << " Text Already in Decrypted.\n";
    }
    else
        cout << " No TEXT.\n";
}

void operator !(Chapter& ch) {
    if (ch.getsize() > 0) {
        if (ch.getCompress() == false) {
            for (int i = 0; i < ch.getsize(); i++) {
                !ch.getarray()[i];
            }
            ch.setCompress(true);
            ch.setDecompress(false);
            cout << "\n\n Text Compressed.\n\n";
        }
        else
            cout << "\n\n Text is Plain.\n\n";
    }
    else
        cout << "\n\n No Text Found.\n\n";
}

void operator --(Chapter& ch) {
    if (ch.getsize() > 0) {
        if (ch.getDecompress() == false) {
            for (int i = 0; i < ch.getsize(); i++) {
                --ch.getarray()[i];
            }
            ch.setCompress(false);
            ch.setDecompress(true);
            cout << "\n\n Text Decompressed.\n\n";
        }
        else
            cout << "\n\n Text is Plain.\n\n";
    }
    else
        cout << "\n\n No Text Found.\n\n";
}

//main.cpp

int main() {
    Chapter myChapter;
    int key = 2;  //Encryption key, can be changed    //works with z + 2 = b 

    ifstream fin("original.txt");
    ofstream fout("copy.txt");
    ofstream freq("Frequency.txt");

    Chapter obj;
    //cout << obj;
    cout << "READING FILE FROM \"original.txt\" \n\n\n";
    fin >> myChapter;
    cout << "Displaying FILE FROM \"original.txt\" on console \n\n\n";
    cout << myChapter << endl << endl << endl;
    fout << myChapter;      //writing to copy.txt
    cout << "Changing to upper case  \n\n\n";
    +myChapter;			//uppercase
    cout << myChapter << endl << endl << endl;
    cout << "Changing to lower case  \n\n\n";
    -myChapter;			//uppercase
    cout << myChapter << endl << endl << endl;

    obj = myChapter;
    cout << "Assignmnet operator ==>  obj  = myChapter and then printing obj \n\n";
    cout << obj << endl << endl;
    bool check;
    check = obj == myChapter;
    cout << endl << "obj == myCHapter is  : " << check << endl << endl << endl;

    cout << myChapter << endl;


    //Encryption
    cout << "Applying encryption to the myChapter and displaying on the screen.\n";
    myChapter + key;
    cout << endl << myChapter << endl << endl << endl;

    cout << "Applying decryption to the myChapter using the key used to encrypt and displaying on the screen.\n";
    //Decryption
    myChapter - key;
    cout << endl << myChapter << endl << endl << endl;

   

    cout << "After applying Compression \n\n";
    !myChapter;     //compression
    //operator!(myChapter);
    cout << myChapter << "\n\n\n";

    cout << "After decompressing the file \n\n";
    --myChapter;    //decompression
    cout << myChapter << "\n\n\n";



    //Input Paragraphs from user
    //  cout << "Instruction:- (to avoid undefined behaviour)\nType '.' to END Sentence.\nType '$' to END Paragraph.\nHit	EnterWhenfinished.\n\nType your text below:-\n";
    //  cin >> myChapter;
    //  cout << endl << myChapter;

    // //write frequency data to file
    myChapter.frequencyData(freq);
    cout << "total chacters in chapter " << myChapter.totalcharacters() << endl;

    myChapter.spellcheck();
    cout << "\nSPELL CHECK DONE WORDS NOT IN DICTIONARY ARE APPENDED TO NEWDICTIONARY.txt\n\n";
}