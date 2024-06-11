#include<iostream>
#include<fstream>
#include<cstring>
//------------------------------------------ [   Class Declaration   ]---------------------------------------
using namespace std;
class Posts;
class User;
class Date;
class Object;
class Page;
class Comment;
class PostContent;
class Activities;
class Memory;
//-------------------------------------------[   Class Defintions   ]--------------------------------------------

class helper
{
public:

	static int StringLenght(const char* str)
	{
		int i = 0;

		for (; str[i] != '\0'; i++) {
		}

		return i;
	}
	static void StringCopy(char*& dest, char* src) {
		char* tempDest = dest;
		for (char* tempSrc = src; *tempSrc != '\0'; tempSrc++, tempDest++)
		{
			*tempDest = *tempSrc;
		}
		*tempDest = '\0';
	}
	static void GetstringFromBuffer(char* str, char*& dest)
	{
		int len1 = StringLenght(str);
		dest = new char[len1 + 1];
		helper::StringCopy(dest, str);

	}
	static bool IssubstringPresent(const char* str, const char* sub) {
		int strLen = StringLenght(str);
		int subLen = StringLenght(sub);


		for (int i = 0; i <= strLen; i++) {

			bool isMatch = true;
			for (int j = 0; j < subLen; j++) {
				if (str[i + j] != sub[j]) {
					isMatch = false;
					break;
				}
			}

			if (isMatch) {
				return true;
			}
		}

		return false;

	}
};
class PostContent {
	//Activities* Content;
public:
	virtual void PrintContent();
	virtual ~PostContent();
};
class Activities : public PostContent {
	int value;
	char* TextAct;
public:
	Activities();
	void setActivity(int, char*);
	void PrintContent();
	~Activities();
};
class Date {
private:
	int day;
	int month;
	int year;
public:
	Date();//default	
	Date(int, int, int);//parametrize
	void print();
	void readdate(ifstream&);
	int getdatediff();
	int CheckMemory();
	~Date();
};
class Posts {
	char* postID;
	Object** LikedBy;
	Comment** CommentByObj;
	PostContent* ActivityBy;
protected:
	char* text;
	Date sharedDate;
	Object* sharedBy;

public:
	Posts();
	void ReadDataFromFile(ifstream&);
	void SetshareData(Object*);
	void SetLikedBy(Object*);
	void ViewLikedBy();
	void ViewSharedBy();
	void PrintPost();
	char* getpostID();
	char* getText();
	Date getdate();
	int postcheckmemory();
	void viewcomments();
	void viewActivity();
	int printdatediff();
	void AddComment(Comment*);
	void AddActivity(PostContent*);
	void Friends();
	virtual ~Posts();
	bool checksharedBy(Object* sharedby) //Function to check shared by for memory
	{
		if (sharedby == sharedBy)
			return true;
		else
			return false;
	}
};
class Memory :public Posts {
private:
	Posts* originalPost;
	char* memorytext;
public:
	Memory();
	void setMemory(char*, User*, Posts*);
	void IsMemoryPresent();
	~Memory();
};
class Object {
	char* ObjID;
protected:
	Posts** Timeline;
public:
	void AddToTimeline(Posts*);
	Object();
	virtual char* getObjId();//virtual
	virtual void ViewTimeline();//virtual
	virtual void PrintName();//virtual
   virtual ~Object();
};
class User :public Object
{
	char* userId;
	char* firstName;
	char* lastName;
	User** FriendList;
	Page** LikedPages;
public:
	//default constructor
	User();
	void AddFriend(User*&);
	void LikePage(Page*&);
	void PrintFriendList();
	void ViewFriendList();
	void ViewLikedPages();
	void ReadDataFromFile(ifstream&);
	void ViewHome();
	//void AddToTimeline(Posts*);

	void ViewFriendTimeline();
	void ViewTimeline();//virtual
	void PrintName();//virtual
	char* getObjId();//virtual
	void ViewMemories();
	char* getId();
	char* getf();
	char* gets();
	~User();

};
class Page :public Object
{
	char* ID;
	char* Title;
public:
	Page();
	void ReadDataFromFile(ifstream&);
	void PrintPageView();
	void ViewPage();
	char* getObjId();//virtual
	void ViewTimeline();//virtual
	void PrintName();//virtual
	void ViewPageTimeline();
	char* getPageId();
	char* getPageTitle();
	~Page();

};
class Comment {
	char* commenttext;
	Object* CommentBy;
public:
	Comment();
	char* getcommenttext();
	void setcommentBy(Object* ptr, char*);
	void PrintComment();
	~Comment();
};
//------------------------------------------------[  Class Functions  ]----------------------------------

//-------------------------------------------[   Functions Of post Content   ]----------------------------
void PostContent::PrintContent() {

}
PostContent::~PostContent() {
	
}
//----------------------------------------------[   Functions Of Activity     ]--------------------------
Activities::Activities() {
	value = 0;
	TextAct = nullptr;
}
void Activities::setActivity(int num, char* text) {
	value = num;
	TextAct = text;
}
void Activities::PrintContent() {
	if (value == 1) {
		cout << " is feeling " << TextAct;
	}
	else if (value == 2) {
		cout << " is thinking about " << TextAct;
	}
	else if (value == 3) {
		cout << " is making " << TextAct;
	}
	else if (value == 4) {
		cout << " is celebrating " << TextAct;
	}
	else {
		cout << "invalid";
	}
}
Activities::~Activities() {
	
	if (TextAct) {
		delete[] TextAct;
	}
}
//-------------------------------------------------[  Functions of Comment  ]-----------------------------
Comment::Comment() {
	commenttext = nullptr;
	CommentBy = nullptr;
}
void Comment::PrintComment() {
	cout << endl;
	CommentBy->PrintName();
	cout << ":";
	cout << endl;
	cout << "\"";
	cout << commenttext;
	cout << "\"";
	cout << endl;
}
void Comment::setcommentBy(Object* ptr, char* text)
{
	commenttext = text;
	CommentBy = ptr;
}
char* Comment::getcommenttext()
{
	return commenttext;
}
Comment::~Comment() {
	
	if (commenttext) {
		delete[] commenttext;
	}
	//CommentBy = 0;
}
//--------------------------------------------------[  Functions of Object  ]-----------------------------
Object::Object() {
	ObjID = nullptr;
	Timeline = nullptr;
}
void Object::AddToTimeline(Posts* setTimeline) {
	if (Timeline == nullptr)
	{
		Timeline = new Posts * [10];
		for (int i = 0;i < 10;i++)
		{
			Timeline[i] = nullptr;
		}
	}

	for (int i = 0;i < 10;i++)
	{
		if (Timeline[i] == nullptr)
		{
			Timeline[i] = setTimeline;
			break;
		}
	}

}
//virtuals\\

char* Object::getObjId() {
	return ObjID;
}
void Object::PrintName() {
	cout << "in obj";
}
void Object::ViewTimeline() {

}
Object::~Object() {
	
	if (ObjID) {
		delete[] ObjID;
	}
	if (Timeline)
	{
		
	/*	for (int i = 0;i < 10;i++)
		{
			if (Timeline[i])
				delete Timeline[i];
		}
		*/
		delete[] Timeline;
	}
}

//-------------------------------------------------[  Functions Of Date  ]-------------------------------------
static Date currentdate(17, 4, 2024);
Date::Date()
{
	day = 0;
	month = 0;
	year = 0;

}
Date::Date(int d, int m, int y)
{
	day = d;
	month = m;
	year = y;
}
void Date::readdate(ifstream& fin) {
	fin >> day >> month >> year;
}
void Date::print()
{
	if (day == currentdate.day && month == currentdate.month && year == currentdate.year)
	{
		cout << "(1h)\n";
	}
	else if (month == currentdate.month && year == currentdate.year) {
		int dayDifference = currentdate.day - day;
		if (dayDifference != 0)
			cout << "(" << dayDifference << "d)\n";
	}
	else {
		cout << "(" << day << "/" << month << "/" << year << "):\n";
	}
}

int Date::getdatediff() {



	if (month == currentdate.month && year == currentdate.year) {
		int diff = -1;
		int dayDifference2 = abs(day - currentdate.day);

		if (dayDifference2 <= 3) {
			diff = dayDifference2;

			return diff;
		}
	}
	
		return -1;
	
}
int Date::CheckMemory()
{
	int diff = -1;
	if (currentdate.day == day && currentdate.month == month && currentdate.year > year)
	{
		cout << "On this day " << currentdate.year - year << " years ago" << endl;
		diff = currentdate.year - year;
		return diff;
	}
	else
	{
		return -1;
	}

}

Date::~Date() {
	//nothing to delete
}

//------------------------------------------------[  Functions Of Posts  ]-------------------------------------
Posts::Posts() {
	postID = nullptr;
	text = nullptr;
	sharedDate = Date();
	sharedBy = nullptr;
	LikedBy = nullptr;
	CommentByObj = nullptr;
	ActivityBy = nullptr;
}
int Posts::printdatediff() {
	int datenum = sharedDate.getdatediff();
	if (datenum <= 3 && datenum != -1)
		return datenum;
	else
		return -1;
}
void Posts::ReadDataFromFile(ifstream& fin) {
	char temp[100];
	fin >> temp;
	helper::GetstringFromBuffer(temp, postID);
	sharedDate.readdate(fin);

	
	fflush(stdin);
	fin.getline(temp, 99);
	helper::GetstringFromBuffer(temp, text);

	cout << endl;

}
void Posts::SetshareData(Object* setShare) {
	if (sharedBy == nullptr)

		sharedBy = setShare;
	else {
		cout << "CANNOT SHARE THE POST!";
	}
}
void Posts::SetLikedBy(Object* setLike)
{
	if (LikedBy == nullptr)
	{
		LikedBy = new Object * [10];
		for (int i = 0;i < 10;i++) {
			LikedBy[i] = nullptr;
		}
	}
	for (int i = 0;i < 10;i++)
	{
		if (LikedBy[i] == nullptr)
		{
			LikedBy[i] = setLike;

			break;
		}
	}
}
void Posts::ViewLikedBy() {
	for (int i = 0;i < 10;i++) {
		if (LikedBy[i] != nullptr)
		{
			cout << LikedBy[i]->getObjId() << "---";	//we need obj id here(like by anyone)
			LikedBy[i]->PrintName();//we need virtual name here(any one can like)
			cout << endl;
		}
	}
}
void Posts::ViewSharedBy() {
	cout << "\nshared by : " << endl;
	cout << sharedBy->getObjId() << endl;
}
void Posts::viewcomments() {

	for (int i = 0;CommentByObj[i] != nullptr;i++) {
		CommentByObj[i]->PrintComment();
	}
	if (CommentByObj == nullptr) {
		cout << "\nThis page has no comments";
	}
}
void Posts::viewActivity() {

	ActivityBy->PrintContent();

}
void Posts::AddComment(Comment* AddComment) {

	if (CommentByObj == nullptr)
	{
		CommentByObj = new Comment * [10];
		for (int i = 0;i < 10;i++) {
			CommentByObj[i] = nullptr;
		}
	}
	for (int i = 0;i < 10;i++)
	{
		if (CommentByObj[i] == nullptr)
		{
			CommentByObj[i] = AddComment;

			break;
		}
	}
}
void Posts::AddActivity(PostContent* AddAct) {
	if (ActivityBy == nullptr)
	{
		ActivityBy = AddAct;

	}
	else {
		cout << "no activity\n";
	}

}
void Posts::PrintPost() {
	if (ActivityBy != nullptr)
		viewActivity();
	sharedDate.print();
	//text
	cout << " \" ";
	cout << text;
	cout << "\"";
	if (CommentByObj != nullptr)
		viewcomments();
	else {
		cout << "  \n";
		//cout << "\nThis post has no comments!!!";
	}
	cout << endl;
}
void Posts::Friends() {
	if (ActivityBy != nullptr)
		viewActivity();

	sharedDate.print();
	cout << endl;
	//text
	cout << "\"";
	cout << text;
	cout << "\"";
	if (CommentByObj != nullptr)
		viewcomments();
	else {
		cout << "  \n";
		//cout << "\nThis post has no comments!!!";
	}
	cout << endl;
}
char* Posts::getpostID() {
	return postID;
}
char* Posts::getText()
{
	return text;
}
Date Posts::getdate() {
	return sharedDate;
}
int Posts::postcheckmemory() {
	int diff = sharedDate.CheckMemory();
	if (diff != -1)
	{
		return diff;
	}
	else
	{
		return -1;
	}
}
Posts::~Posts() {
	
	if (postID) {
		delete[] postID;
	}
	if (text) {
		delete[] text;
	}
	sharedBy = 0;
	if (ActivityBy) {
		delete ActivityBy;
	}
	if (LikedBy) {
		delete[] LikedBy;
	}
	if (CommentByObj) {
		delete[] CommentByObj;
	}
}
//-------------------------------------------------[  Functions Of Memories  ]----------------------------
Memory::Memory() {

	originalPost = nullptr;
	memorytext = 0;
}

void Memory::setMemory(char* temp, User* curr, Posts* oldpostptr)
{
	//set for posts attributes too

	memorytext = temp;
	text = temp;
	sharedBy = curr;
	sharedDate = currentdate;
	originalPost = oldpostptr;

}
void Memory::IsMemoryPresent() {
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	sharedBy->PrintName();
	cout << " Shared a memory~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << text;
	cout <<"\n";
	
	sharedBy->PrintName();
	originalPost->PrintPost();

}

Memory::~Memory() {
	//does nothing	
}

//------------------------------------------------[  Functions Of page  ]-------------------------------------
Page::Page() {
	ID = nullptr;
	Title = nullptr;
}
void Page::ReadDataFromFile(ifstream& fin) {
	//initializations
	char temp[100];
	fin >> temp;
	int len1 = helper::StringLenght(temp);
	ID = new char[len1 + 1];
	helper::StringCopy(ID, temp);
	fin.getline(temp, 99);
	int len2 = helper::StringLenght(temp);
	Title = new char[len2 + 1];
	helper::StringCopy(Title, temp);
}

void Page::PrintPageView() {
	cout << ID << "\t" << Title << "\t";
}
void Page::ViewPage() {
	cout << "Command: View Page (" << ID << ")";
	cout << Title << ":\n";
	for (int i = 0;Timeline[i] != nullptr;i++) {
		cout << Title;
		Timeline[i]->PrintPost();
	}
}
void Page::ViewTimeline()//virtual
{
	if (Timeline)
		for (int i = 0;Timeline[i] != nullptr;i++)
		{

			cout <<"--" << Title;

			Timeline[i]->PrintPost();
		}
}
void Page::ViewPageTimeline() {
	if (Timeline != nullptr)
		for (int i = 0;Timeline[i] != nullptr;i++)
		{
			int num = Timeline[i]->printdatediff();
			if (num <= 3 && num != -1) {

				cout << "--" << Title;

				Timeline[i]->Friends();
			}
		}
}
void Page::PrintName() 
{//virtual
	cout << Title;
}

char* Page::getObjId() {//virtual
	return ID;
}
char* Page::getPageId() {
	return ID;
}
char* Page::getPageTitle() {
	return Title;
}

Page::~Page() {
	
	delete[] ID;
	if (Title)
		delete[] Title;
	
}

// --------------------------------------------------[  Functions Of User  ]---------------------------------------
User::User() {
	userId = nullptr;
	firstName = nullptr;
	lastName = nullptr;
	FriendList = nullptr;
	LikedPages = nullptr;

}
void User::AddFriend(User*& AddUserFriend) {
	if (FriendList == nullptr) {
		FriendList = new User * [10];
		for (int i = 0;i < 10;i++) {
			FriendList[i] = nullptr;
		}
	}

	for (int i = 0;i < 10;i++) {
		if (FriendList[i] == nullptr) {
			FriendList[i] = AddUserFriend;
			break;
		}
	}
}
void User::LikePage(Page*& AddLikePage) {
	if (LikedPages == nullptr) {
		LikedPages = new Page * [10];
		for (int i = 0;i < 10;i++) {
			LikedPages[i] = nullptr;
		}
	}
	for (int i = 0;i < 10;i++) {

		if (LikedPages[i] == nullptr) {
			LikedPages[i] = AddLikePage;
			break;

		}
	}
}
void User::PrintFriendList() {
	cout << userId << "\t" << firstName << "\t" << lastName;
}
void User::ViewFriendList() {
	int check = 0;
	for (int i = 0; i < 10; i++) {
		if (FriendList[i] != nullptr) {
			check = 1;
			FriendList[i]->PrintFriendList();
			cout << endl;
		}
	}
	if (check==0) {
		cout << "no friend of user";
	}
}
void User::ViewLikedPages() {
	int check = 0;
	for (int i = 0; i < 10; i++) {
		if (LikedPages[i] != nullptr) {
			check = 1;
			LikedPages[i]->PrintPageView();
			cout << endl;
		}
	}
	if (check==0) {
		cout << "no like page";
	}
}

void User::ReadDataFromFile(ifstream& fin) {
	//initializations		
	char temp[100];
	fin >> temp;
	int len1 = helper::StringLenght(temp);
	userId = new char[len1 + 1];
	helper::StringCopy(userId, temp);
	fin >> temp;
	int len2 = helper::StringLenght(temp);
	firstName = new char[len2 + 1];
	helper::StringCopy(firstName, temp);

	//second name
	fin >> temp;
	int len3 = helper::StringLenght(temp);
	lastName = new char[len3 + 1];
	helper::StringCopy(lastName, temp);

}

void User::ViewTimeline()//virtual
{
	int check = 0;
	for (int i = 0;Timeline[i] != nullptr;i++)
	{

		check = 1;

		cout << "--" << firstName << " " << lastName;


		Timeline[i]->PrintPost();

	}
	if (check==0) {
		cout << "no shared pages in timeline";
	}
}
void User::ViewFriendTimeline() {
	for (int i = 0;Timeline[i] != nullptr;i++)
	{
		int num = Timeline[i]->printdatediff();
		if (num <= 3 && num != -1) {
			cout << "--" << firstName << " " << lastName;

			Timeline[i]->Friends();
		}

	}
}
void User::PrintName()
{//virtual
	cout << firstName << " " << lastName;
}
void User::ViewHome() {
	if(Timeline)

	for (int i = 0;Timeline[i] != nullptr;i++)
	{
		int num = Timeline[i]->printdatediff();

		if (num <= 3 && num != -1) {
			cout << "--" << firstName << " " << lastName;
			Timeline[i]->PrintPost();

		}


		for (int i = 0;FriendList[i] != nullptr;i++) {

			if (num <= 3 && num != -1)
				FriendList[i]->ViewFriendTimeline();
		}
		for (int i = 0;LikedPages[i] != nullptr;i++) {

			if (num <= 3 && num != -1)
				LikedPages[i]->ViewPageTimeline();
		}
	}

}
void User::ViewMemories() {
	if(Timeline)
	for (int i = 0;Timeline[i] != nullptr;i++) {
		if (Timeline[i]) {
			int diff = Timeline[i]->postcheckmemory();
			if (diff != -1) {
				cout << firstName << " " << lastName;
				Timeline[i]->PrintPost();
			}

			//else {
			//	//cout<<"No Memories for " << firstName << " " << lastName<<"\n";
			//	continue;
			//}
		}
	}

}

char* User::getObjId() {
	//virtual
	return userId;
}
char* User::getId() {
	return userId;
}
char* User::getf() {
	return firstName;
}
char* User::gets() {
	return lastName;
}

User::~User() {
	
	if(userId)
	delete[] userId;
	if(firstName)
	delete[] firstName;
	if(lastName)
	delete[] lastName;
	if (FriendList)
    delete[] FriendList;
	if (LikedPages) 
	delete[] LikedPages;
	
}


//--------------------------------------------------------[  CONTROLLER CLASS  ]--------------------------------------------
class controller {

	User** Alluser;
	Page** Allpages;
	Posts** Allposts;
	Comment** AllComments;
	Activities** AllActivities;

public:

	//constructor
	controller() {
		Alluser = nullptr;
		Allpages = nullptr;
		Allposts = nullptr;
		AllComments = nullptr;
		AllActivities = nullptr;

	}
	//loading users
	void LoadAllUsers(const char* Filename) {
		int totaluser;
		ifstream inputFile;
		inputFile.open(Filename);
		if (inputFile)
		{
			inputFile >> totaluser;
			Alluser = new User * [totaluser];
			for (int i = 0;i < totaluser;i++)
			{
				Alluser[i] = new User;
				Alluser[i]->ReadDataFromFile(inputFile);
			}
		}
		else
		{
			cout << "error opening the file\n";
		}
	}

	//loading pages
	void LoadAllPages(const char* Filename) {
		int totalpages;
		ifstream inputFile;
		inputFile.open(Filename);
		if (inputFile) {
			inputFile >> totalpages;
			Allpages = new Page * [totalpages];

			for (int i = 0;i < totalpages;i++) {
				Allpages[i] = new Page;
				Allpages[i]->ReadDataFromFile(inputFile);
				
			}
		}
		else {
			cout << "error openingthe file\n";
		}
	}

	//search functions
	Posts* searchPostByID(const char* Id) {
		for (int i = 0;i < 12;i++) {//for now hardcode 20
			bool present = helper::IssubstringPresent(Allposts[i]->getpostID(), Id);
			if (present) {
				return Allposts[i];
			}
		}
		return nullptr;
	}
	Object* searchObject(const char* Id) {
		if (Id[0] == 'u') {
			return searchUserByID(Id);

		}
		if (Id[0] == 'p') {
			return searchPageByID(Id);
		}
		else {
			return 0;
		}
	}
	User* searchUserByID(const char* Id) {
		for (int i = 0;i < 20;i++) {//for now hardcode 20
			bool present = helper::IssubstringPresent(Alluser[i]->getId(), Id);
			if (present) {
				return Alluser[i];
			}
		}
		return nullptr;
	}
	Page* searchPageByID(const char* Id) {
		for (int i = 0;i < 12;i++) {//for now hardcode 20
			bool present = helper::IssubstringPresent(Allpages[i]->getPageId(), Id);
			if (present) {
				return Allpages[i];
			}
		}
		return nullptr;
	}

	//loading and linking from file
	void LoadAllPosts(const char* filename) {
		int totalPosts;
		ifstream inputFile;
		inputFile.open(filename);
		if (inputFile)
		{
			inputFile >> totalPosts;
			Allposts = new Posts * [totalPosts];
			char sharedtemp[20];
			for (int i = 0;i < totalPosts;i++)
			{
				Allposts[i] = new Posts;
				Allposts[i]->ReadDataFromFile(inputFile);

				inputFile >> sharedtemp;

				if (sharedtemp[0] == 'u') {
					User* ptr = searchUserByID(sharedtemp);
					if (ptr != nullptr) {
						Allposts[i]->SetshareData(ptr);
						ptr->AddToTimeline(Allposts[i]);
					}//agar inherit hoga object tabhi object ka parameter jaye ga
				}
				else
				{
					Page* ptr = searchPageByID(sharedtemp);
					if (ptr != nullptr) {
						Allposts[i]->SetshareData(ptr);
						ptr->AddToTimeline(Allposts[i]);
					}
				}
				inputFile >> sharedtemp;

				while (!helper::IssubstringPresent(sharedtemp, "-1"))
				{

					if (sharedtemp[0] == 'u')
					{

						User* ptr = searchUserByID(sharedtemp);
						if (ptr != nullptr) {
							Allposts[i]->SetLikedBy(ptr);

						}//agar inherit hoga object tabhi object ka parameter jaye ga
					}
					else
					{

						Page* ptr = searchPageByID(sharedtemp);
						if (ptr != nullptr) {
							Allposts[i]->SetLikedBy(ptr);
						}
					}
					inputFile >> sharedtemp;
				}

			}

		}
		else {
			cout << "error opening the file!\n";
		}
	}
	void LoadAllComments(const char* filename) {
		int totalcomments = 0;
		ifstream inputFile;
		inputFile.open(filename);
		if (inputFile)
			inputFile >> totalcomments;

		AllComments = new Comment * [totalcomments];
		for (int i = 0;i < totalcomments;i++) {

			char temp[100];
			char* postId = nullptr;
			char* userId = nullptr;
			char* text = nullptr;
			inputFile >> temp;
			helper::GetstringFromBuffer(temp, postId);
			inputFile >> temp;
			helper::GetstringFromBuffer(temp, userId);
			fflush(stdin);
			inputFile.getline(temp, 99);

			helper::GetstringFromBuffer(temp, text);
			//searhh post
			Posts* postPtr = searchPostByID(postId);
			//search comment
			Object* tempObjId = searchObject(userId);
			AllComments[i] = new Comment;
			AllComments[i]->setcommentBy(tempObjId, text);
			postPtr->AddComment(AllComments[i]);

		}
	}
	void linkUsersAndPages(const char* fin) {
		ifstream inputFile;

		inputFile.open(fin);
		if (inputFile) {
			char ID[10];
			while (inputFile >> ID && !helper::IssubstringPresent(ID, "-1"))
			{
				User* temp = searchUserByID(ID);
				if (!temp) {
					cout << "User with ID " << ID << " not found" << endl;
					continue;
				}

				while (inputFile >> ID && !helper::IssubstringPresent(ID, "-1")) {
					User* friendUser = searchUserByID(ID);
					if (friendUser) {
						temp->AddFriend(friendUser);
					}
					if (friendUser == nullptr) {
						cout << "no friends";
						break;
					}
				}
				while (inputFile >> ID && !helper::IssubstringPresent(ID, "-1")) {
					Page* page = searchPageByID(ID);
					if (page) {
						temp->LikePage(page);
					}
					if (page == nullptr) {
						cout << "no liked pages";
						break;
					}
				}
			}
			inputFile.close();
		}

	}
	void LoadAllActivities(const char* fin) {
		int totalActivities = 0;
		ifstream inputFile;
		inputFile.open(fin);
		if (fin) {
			inputFile >> totalActivities;
			AllActivities = new Activities * [totalActivities];
			for (int i = 0;i < totalActivities;i++) {
				char temp[100];
				char* ActId = nullptr;
				int num = 0;
				char* Activitytext = nullptr;
				//int num = 0;
				inputFile >> temp;
				helper::GetstringFromBuffer(temp, ActId);
				inputFile >> num;
				fflush(stdin);
				inputFile.getline(temp, 99);

				helper::GetstringFromBuffer(temp, Activitytext);
				Posts* actPtr = searchPostByID(ActId);
				if (actPtr != nullptr) {
					AllActivities[i] = new Activities;
					AllActivities[i]->setActivity(num, Activitytext);
					actPtr->AddActivity(AllActivities[i]);
				}

			}

		}
	}

	//running functions

	void Run()
	{
		char currentID[] = "u7";
		User* currentUser = searchUserByID("u7");

		//viewing liked pages and friend lists

		cout << "Command:\tSet current User" << "\"" << currentID << "\"" << endl;
		if (currentUser) {
			cout << currentUser->getf() << " " << currentUser->gets() << " User Successfully Set as Current user\n";
			cout << "\n----------------------------------\n";
			cout << "\nCommand:\tView Friend List\n";
			cout << "\n----------------------------------\n";
			cout << currentUser->getf() << currentUser->gets() << "-Friend List\n";
			currentUser->ViewFriendList();
			cout << "-----------------------------------\n";
			cout << "Command:\tView Liked Pages";
			cout << "\n------------------------------------\n";
			cout << currentUser->getf() << currentUser->gets() << "-Liked Pages\n";
			currentUser->ViewLikedPages();
			cout << endl;
		}
		else {
			cout << "User Not Found!\n";
		}

		//printing timeline

		cout << "\n------------------------------\n";
		cout << "Command:\tView Timeline";
		cout << "\n-------------------------------\n";

		User* userptr = searchUserByID("u7");
		cout << currentUser->getf() << currentUser->gets() << "-Timeline\n";
		if (userptr != nullptr)
			userptr->ViewTimeline();
		else {
			cout << "Timeline not available\n";
		}

		//printing likedlists/ like a post

		char postID[10] = "post5";
		cout << "-----------------------------------\n";
		cout << "\nCommand:\tView Liked List(" << postID << ")\n";
		cout << "-----------------------------------\n";
		Posts* postptr = searchPostByID(postID);
		if (postptr != nullptr) {
			cout << "Post Liked By:\n";
			postptr->ViewLikedBy();
			cout << "-----------------------------------\n";
			cout << "\nCommand: Like Post(" << postptr->getpostID() << ")\n";
			cout << "-----------------------------------\n";
			cout << "\nCommand:\tView Liked List(" << postptr->getpostID() << ")\n\n";
			cout << "-----------------------------------\n";
			postptr->SetLikedBy(userptr);
			cout << "Post Liked By:\n";
			postptr->ViewLikedBy();
		}
		else
		{
			cout << "Post Not Found";
		}

		//view a page

		char pageID[5] = "p1";
		cout << "-----------------------------------\n";
		cout << "\nCommand:\tViewPage" << pageID << "\n\n";
		cout << "-----------------------------------\n";
		Page* pageptr = searchPageByID(pageID);
		if (pageptr != nullptr)
			pageptr->ViewPage();
		else
		{
			cout << "page not found";
		}

		//view home

		cout << "----------------------------------\n";
		cout << "Command:\tView Home\n";
		cout << "----------------------------------\n";

		//posting comments

		User* currentUserObj = searchUserByID("u7");
		if (currentUserObj != nullptr)
		{
			currentUserObj->ViewHome();
			//posting a comment 1
			cout << "----------------------------------\n";
			cout << "Command:\tPost Comment\n";
			cout << "----------------------------------\n";
			char postIDObj[10] = "post8";
			char temptext[] = "Thanks for the wishes";
			cout << "Command:\tPostComment(" << postIDObj << "," << temptext << ")\n";
			cout << "Command:\tViewPost(" << postIDObj << ")\n";

			Posts* postPtrC = searchPostByID(postIDObj);
			if (postPtrC != nullptr)
			{
				Comment* commentToBeDone2 = new Comment;

				commentToBeDone2->setcommentBy(currentUserObj, temptext);
				postPtrC->AddComment(commentToBeDone2);
				currentUserObj->ViewTimeline();
			}

		}
		else
		{
			cout << "object not found";
		}

		//posting a comment 2

		cout << "----------------------------------\n";
		cout << "Command:\tPost Comment--2\n";
		cout << "----------------------------------\n";
		User* currentUserObj2 = searchUserByID("u12");
		if (currentUserObj2) {
			char postIDObj2[10] = "post4";
			char temptext2[] = "Thankyou for good luck";
			cout << "Command:\tPostComment(" << postIDObj2 << "," << temptext2 << ")\n";
			cout << "Command:\tViewPost(" << postIDObj2 << ")\n";

			Posts* postPtrC2 = searchPostByID(postIDObj2);
			if (postPtrC2 != nullptr)
				//for (int i = 0;AllComments[i]!=nullptr;i++) 
			{
				Comment* commentDone2 = new Comment;

				commentDone2->setcommentBy(currentUserObj2, temptext2);
				postPtrC2->AddComment(commentDone2);

				currentUserObj2->ViewTimeline();
			}
			else {
				cout << "page not found";
			}
		}
		else {
			cout << "User Not found to view comments etc \n";
		}
			//viewing memories

			User* currentUserObjM = searchUserByID("u7");
			cout << "----------------------------------\n";
			cout << "Command:\tView Memories\n";
			cout << "----------------------------------\n";
			cout << "\nWe hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago.\n";
			cout << currentUserObjM->getf() << currentUserObjM->gets() << "-Memories\n";
			currentUserObjM->ViewMemories();

			//sharing a memory

			cout << "----------------------------------\n";
			cout << "Command:\tShare Memory\n";
			cout << "----------------------------------\n";
			char postIDObj3[10] = "post10";
			char temptext3[] = "Never thought I would Be Specialist In This Feild";
			cout << "Command:\tPostMemory(" << postIDObj3 << "," << temptext3 << ")\n";
			cout << "Command:\tViewing Memory for(" << postIDObj3 << ")\n";
			Posts* oldpostPtr = searchPostByID(postIDObj3);
			User* temp = searchUserByID("u7");
			if (oldpostPtr->checksharedBy(temp)) {
				if (oldpostPtr != nullptr) {
					Memory* memPtr = new Memory;

					memPtr->setMemory(temptext3, temp, oldpostPtr);
					memPtr->IsMemoryPresent();

					temp->AddToTimeline(memPtr);

					temp->ViewTimeline();
				}
				else {
					cout << "post not found!\n";
				}
			}
			else {
				cout << "No memory shared !\n";
			}

		
	}
	void LoadData() {
		LoadAllUsers("SocialNetworkUsers.txt");
		LoadAllPages("SocialNetworkPages.txt");
		linkUsersAndPages("UsersFriendsAndLikedPages.txt");
		LoadAllPosts("socialNetworkPosts.txt");
		LoadAllComments("SocialNetworkComments.txt");
		LoadAllActivities("SocialNetworkActivities.txt");

	}
	~controller() {
		
		if (Alluser) {
			for (int i = 0;i < 20;i++) {

				delete Alluser[i];
			}
			delete[] Alluser;
		}
		if (Allpages) {
			for (int i = 0;i < 12;i++) {
				delete Allpages[i];
			}
			delete[] Allpages;
		}
		if (Allposts) {
			delete[] Allposts;
		}
		if (AllComments) {
			delete[] AllComments;
		}
		
	}
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/////\\\\\\\[  MAIN  ]\\\\\\\\////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main()
{
	
		controller mainapp;
		mainapp.LoadData();
		mainapp.Run();
	
	//system("pause");
	return 0;

}




