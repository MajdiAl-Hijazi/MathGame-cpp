#include <iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

enum enLevelQuestion { Easy = 1 ,Midum = 2 ,Hard = 3 ,MixLevel = 4 };

enum enOperatorType { Sum = 1 ,Sub = 2 ,Mult = 3 ,Div = 4 ,MixOpertor = 5 };

struct stInfoGame {

    int NumberOfQuestions;
    enLevelQuestion LevelQuestions;
    enOperatorType OperatorType;
    int NumberOfRightAnswers = 0;
    int NumberOfWrongAnswers = 0;
};

int RandomNumber(int from, int to) {

    return rand() % (to - from + 1) + from;
}

int ReadNumber(string Message) {

    int Number;
    
    do
    {

        cout << Message;
        cin >> Number;
    } while (Number <= 0);

    return Number;
}

void ChoiceNum1AndNum2(int& Num1, int& Num2, enLevelQuestion& levelQuestion) {

    switch (levelQuestion) {
    
    case enLevelQuestion::Easy:
        Num1 = RandomNumber(1, 33);
        Num2 = RandomNumber(1, 33);
        break;
    case enLevelQuestion::Midum:
        Num1 = RandomNumber(33, 66);
        Num2 = RandomNumber(33, 66);
        break;
    case enLevelQuestion::Hard:
        Num1 = RandomNumber(66, 100);
        Num2 = RandomNumber(66, 100);
        break;
    case enLevelQuestion::MixLevel:
        Num1 = RandomNumber(1, 100);
        Num2 = RandomNumber(1, 100);
        break;
    default:
        cout << "Error";
    }
}

char ChoiceMixOpertator() {

    enOperatorType MixOperator = (enOperatorType)RandomNumber(1 ,4);

    switch (MixOperator) {
    
    case enOperatorType::Sum:
        return '+';
    case enOperatorType::Sub:
        return '-';
    case enOperatorType::Mult:
        return '*';
    case enOperatorType::Div:
        return '/';
    default:
        cout << "Error" << endl;
    }
}

char ChoiceOperator(enOperatorType& OperatorType) {

    switch (OperatorType) {
    
    case enOperatorType::Sum:
            return '+';
    case enOperatorType::Sub:
        return '-';
    case enOperatorType::Mult:
        return '*';
    case enOperatorType::Div:
        return '/';
    case enOperatorType::MixOpertor:
        return ChoiceMixOpertator();
    default:
        cout << "Error" << endl;
    }
}

int FindAnswerQuestion(int& Num1 , int& Num2 ,char& Operator) {

    switch (Operator) {
    
    case '+':
        return Num1 + Num2;
    case '-':
        return Num1 - Num2;
    case '*':
        return Num1 * Num2;
    case '/':
        return Num1 / Num2;
    }
}

void CheckUserAnswer(int& UserAnswer ,int& CorrectAnswer ,stInfoGame& InfoGame) {

    if (UserAnswer == CorrectAnswer) {
    
        InfoGame.NumberOfRightAnswers++;
        system("color 2F");
        cout << "Right Answer :-)" << endl;
    }
    else {
    
        InfoGame.NumberOfWrongAnswers++;
        system("color 4F");
        cout << "Wrong Answer :-(" << endl;
    }
}

void DisplayOneQuestion(stInfoGame& InfoGame) {

    int Num1, Num2, Result, UserAnswer ,CorrectAnswer;
    char Operator;

    for (int i = 1; i <= InfoGame.NumberOfQuestions; i++) {
    
        Num1 = 0;
        Num2 = 0;
        Result = 0;
        ChoiceNum1AndNum2(Num1 ,Num2 ,InfoGame.LevelQuestions);
        Operator = ChoiceOperator(InfoGame.OperatorType);
        cout << "\n\nQuestion [" << i << "/" << InfoGame.NumberOfQuestions << "]\n\n" << endl;
        cout << Num1 << endl << Num2 << " " << Operator << endl << "___________" << endl;
        CorrectAnswer = FindAnswerQuestion(Num1 ,Num2 ,Operator);
        cin >> UserAnswer;
        CheckUserAnswer(UserAnswer ,CorrectAnswer ,InfoGame);

    }
}

string ShowQuestionLevel(enLevelQuestion level) {

    switch (level) {
    
    case enLevelQuestion::Easy:
        return "easy";
    case enLevelQuestion::Midum:
        return "Medium";
    case enLevelQuestion::Hard:
        return "Hard";
    case enLevelQuestion::MixLevel:
        return "MixLevel";
    }
}

string ShowOperatorType(enOperatorType Operator) {

    switch (Operator) {

    case enOperatorType::Sum:
        return "+";
    case enOperatorType::Sub:
        return "-";
    case enOperatorType::Mult:
        return "*";
    case enOperatorType::Div:
        return "/";
    case enOperatorType::MixOpertor:
        return "MixOperator";
    }
}

void FinalEmojy (stInfoGame InfoGame) {

    if (InfoGame.NumberOfRightAnswers > InfoGame.NumberOfWrongAnswers)
        cout << "Pass :-)";
    else if (InfoGame.NumberOfWrongAnswers > InfoGame.NumberOfRightAnswers)
        cout << "Fail :-(";
    else
        cout << "Draw";
}

void DisplayFinalResult(stInfoGame InfoGame) {

    cout << "\n\n-----------------------------------------------\n" << endl;
    cout << "  Final Result is ";
    FinalEmojy(InfoGame);
    cout << "\n\n-----------------------------------------------" << endl;
    cout << "Number of Question         : " << InfoGame.NumberOfQuestions << endl;
    cout << "Question level             : " << ShowQuestionLevel(InfoGame.LevelQuestions) << endl;
    cout << "Operator                   : " << ShowOperatorType(InfoGame.OperatorType) << endl;
    cout << "Number of Right Answers    : " << InfoGame.NumberOfRightAnswers << endl;
    cout << "Number of Wrong Answers    : " << InfoGame.NumberOfWrongAnswers << endl;
    cout << "-----------------------------------------------" << endl;
}

void PlayGame() {

    stInfoGame InfoGame;
    InfoGame.NumberOfQuestions = ReadNumber("How many question do you want ? ");
    InfoGame.LevelQuestions = (enLevelQuestion)ReadNumber("Enter question level [1]:Easy, [2]:Midum, [3]:Hard, [4]:Mix ? ");
    InfoGame.OperatorType = (enOperatorType)ReadNumber("Enter operator type [1]:Add ,[2]:Sub ,[3]:Mult ,[4]:Div ,[5]:Mix ? ");
    DisplayOneQuestion(InfoGame);
    DisplayFinalResult(InfoGame);

}

void ResetScreen() {

    system("cls");
    system("color 07");
}

void StartGame() {

    char PlayAgain = 'Y';

    do {
    
        ResetScreen();
        PlayGame();
        cout << "\n\nDo you want play again (Y/N) ? ";
        cin >> PlayAgain;
        
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main() {

    srand(time(0));
    StartGame();
        
    return 0;
}
