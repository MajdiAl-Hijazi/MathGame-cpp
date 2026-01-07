#include <iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

enum enOperationType { Add = 1 ,Sub = 2 ,Mult = 3 ,Div = 4 ,MixOp = 5 };

enum enQuestionLevel { EasyLevel = 1 ,MedLevel = 2 ,HardLevel = 3 ,Mix = 4 };

struct stQuestion {

    int Number1 = 0;
    int Number2 = 0;
    enOperationType OperationType;
    enQuestionLevel QuestionLevel;
    int CorrectAnswer = 0;
    int PlayerAmswer = 0;
    bool AnswerResult = false;
};

struct stQuizz {

    stQuestion QuestionList[100];
    short NumberOfQuestion;
    enQuestionLevel QuestionLevel;
    enOperationType OpType;
    short NumberOfWrongAnswers = 0;
    short NumberOfRightAnswers = 0;
    bool isPass = false;
};

short ReadHowManyQuestion() {

    short NumberOfQuestion;

    do {
    
        cout << "How many question do you want to answer ? ";
        cin >> NumberOfQuestion;
    } while (NumberOfQuestion < 1 || NumberOfQuestion > 10);

    return NumberOfQuestion;
}

enQuestionLevel ReadQuestionLevel() {

    short QuestionLevel = 0;

    do
    {

        cout << "Enter question level [1] Easy ,[2] Med ,[3] Hard ,[4] Mix  ? ";
        cin >> QuestionLevel;
    } while (QuestionLevel < 1 || QuestionLevel > 4);

    return (enQuestionLevel)QuestionLevel;
}

enOperationType ReadOpType() {

    short OpType = 0;

    do
    {

        cout << "Enter question type [1] Add ,[2] sub ,[3] Mul ,[4] Div ,[5] Mix ? ";
        cin >> OpType;
    } while (OpType < 1 || OpType > 5);

    return (enOperationType)OpType;
}

int RandomNumber(int From ,int To) {

    return rand() % (To - From + 1) + From;
}

enOperationType GetRandomOperationType() {

    int Op = RandomNumber(1 ,4);
    return (enOperationType)Op;
}

int SimpleCalculator(int Number1 , int Number2 ,enOperationType OpType) {

    switch (OpType) {
    
    case enOperationType::Add:
        return Number1 + Number2;
    case enOperationType::Sub:
        return Number1 - Number2;
    case enOperationType::Mult:
        return Number1 * Number2;
    case enOperationType::Div:
        return Number1 / Number2;
    default:
        return Number1 + Number2;
    }
}

stQuestion GenerateQuestion(enQuestionLevel QuestionLevel ,enOperationType OpType) {

    stQuestion Question;

    if (QuestionLevel == enQuestionLevel::Mix)
        QuestionLevel = (enQuestionLevel)RandomNumber(1 ,3);
    if (OpType == enOperationType::MixOp)
        OpType = GetRandomOperationType();

    Question.OperationType = OpType;

    switch (QuestionLevel) {
    
    case enQuestionLevel::EasyLevel:
        Question.Number1 = RandomNumber(1 ,10);
        Question.Number2 = RandomNumber(1 ,10);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1 ,Question.Number2 ,Question.OperationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;

    case enQuestionLevel::MedLevel:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;

    case enQuestionLevel::HardLevel:
        Question.Number1 = RandomNumber(50 ,100);
        Question.Number2 = RandomNumber(50, 100);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;
    }
}

void GenerateQuizzQuestion(stQuizz& Quizz) {

    for (short Question = 0; Question < Quizz.NumberOfQuestion; Question++)
        Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionLevel ,Quizz.OpType);
}

string GetOpTypeSymbol(enOperationType OpType) {

    switch (OpType)
    {
    case enOperationType::Add:
        return "+";
    case enOperationType::Sub:
        return "-";
    case enOperationType::Mult:
        return "x";
    case enOperationType::Div:
        return "/";
    default:
        return "Mix";
    }
}

void PrintQuestion(stQuizz& Quizz ,short QuestionNumber) {

    cout << "\n";
    cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestion << "]\n\n";
    cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
    cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
    cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
    cout << "\n__________" << endl;
}

int ReadQuestionAnswer() {

    int Answer = 0;
    cin >> Answer;
    return Answer;
}

void SetScreenColor(bool AnswerResult) {

    AnswerResult ? (system("color 2F")) : (system("color 4F"));
}

void CorrectTheQuestionAnswer(stQuizz& Quizz ,short QuestionNumber) {

    if (Quizz.QuestionList[QuestionNumber].PlayerAmswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer) {
    
        Quizz.QuestionList[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrongAnswers++;
        cout << "Wrong Answer :-(\n";
        cout << "The Right Answer is : ";
        cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer;
        cout << "\n";
    }
    else {
    
        Quizz.QuestionList[QuestionNumber].AnswerResult = true;
        Quizz.NumberOfRightAnswers++;
        cout << "Right Answer :-)\n";
    }

    cout << "\n";
    SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz) {

    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestion; QuestionNumber++) {
    
        PrintQuestion(Quizz ,QuestionNumber);
        Quizz.QuestionList[QuestionNumber].PlayerAmswer = ReadQuestionAnswer();
        CorrectTheQuestionAnswer(Quizz ,QuestionNumber);
    }

    Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

string GetFinalResulText(bool isPass) {

    return ( isPass ?  "PASS :-)" : "FAIL :-(" );
}

string GetQuestionLevelTwxt(enQuestionLevel QuestionLevel) {

    string arrQuestionLevel[4] = { "Easy" ,"Med" ,"Hard" ,"Mix" };
    return arrQuestionLevel[QuestionLevel - 1];
}

void PrintQuizzResult(stQuizz Quizz) {

    cout << "\n";
    cout << "______________________________\n\n";
    cout << "Final Result is " << GetFinalResulText(Quizz.isPass) << endl;
    cout << "______________________________\n\n";
    cout << "Number of question     : " << Quizz.NumberOfQuestion << endl;
    cout << "Questiob level         : " << GetQuestionLevelTwxt(Quizz.QuestionLevel) << endl;
    cout << "OpType                 : " << GetOpTypeSymbol(Quizz.OpType) << endl;
    cout << "Number of Right answer : " << Quizz.NumberOfRightAnswers << endl;
    cout << "Number of Wrong answer : " << Quizz.NumberOfWrongAnswers << endl;
    cout << "______________________________\n";
}

void PlayMathGame() {

    stQuizz Quizz;
    Quizz.NumberOfQuestion = ReadHowManyQuestion();
    Quizz.QuestionLevel = ReadQuestionLevel();
    Quizz.OpType = ReadOpType();
    GenerateQuizzQuestion(Quizz);
    AskAndCorrectQuestionListAnswers(Quizz);
    PrintQuizzResult(Quizz);
}

void ResetScreen() {

    system("color 7");
    system("cls");
}

void StartGame() {

    char PlayAgain = 'y';

    do
    {
        ResetScreen();
        PlayMathGame();
        cout << endl << "Do you want to play again Y/N ? ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main() {

    srand((unsigned)time(NULL));
    StartGame();

    return 0;
}
