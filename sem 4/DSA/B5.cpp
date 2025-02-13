#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Subsection {
public:
    string title;

    Subsection(string title) {
        this->title = title;
    }

    void display() {
        cout << "    Subsection: " << title << endl;
    }
};

class Section {
public:
    string title;
    vector<Subsection> subsections;

    Section(string title) {
        this->title = title;
    }

    void addSubsection(Subsection subsection) {
        subsections.push_back(subsection);
    }

    void display() {
        cout << "   Section: " << title << endl;
        for (auto& subsection : subsections) {
            subsection.display();
        }
    }
};

class Chapter {
public:
    string title;
    vector<Section> sections;

    Chapter(string title) {
        this->title = title;
    }

    void addSection(Section section) {
        sections.push_back(section);
    }

    void display() {
        cout << "  Chapter: " << title << endl;
        for (auto& section : sections) {
            section.display();
        }
    }
};

class Book {
public:
    string name;
    vector<Chapter> chapters;

    Book(string name) {
        this->name = name;
    }

    void addChapter(Chapter chapter) {
        chapters.push_back(chapter);
    }

    void display() {
        cout << " Book Name: " << name << endl;
        for (auto& chapter : chapters) {
            chapter.display();
        }
    }
};

int main() {
    string bookName;
    cout << "Enter the name of the book: ";
    getline(cin, bookName);
    
    Book book(bookName);
    
    int numChapters;

    cout << "Enter the number of chapters: ";
    cin >> numChapters;
    cin.ignore();

    for (int i = 0; i < numChapters; ++i) {
        string chapterTitle;
        cout << "Enter the title for chapter " << i + 1 << ": ";
        getline(cin, chapterTitle);

        Chapter chapter(chapterTitle);

        int numSections;
        cout << "Enter the number of sections in chapter '" << chapterTitle << "': ";
        cin >> numSections;
        cin.ignore();

        for (int j = 0; j < numSections; ++j) {
            string sectionTitle;
            cout << "Enter the title for section " << j + 1 << " in chapter '" << chapterTitle << "': ";
            getline(cin, sectionTitle);

            Section section(sectionTitle);

            int numSubsections;
            cout << "Enter the number of subsections in section '" << sectionTitle << "': ";
            cin >> numSubsections;
            cin.ignore();

            for (int k = 0; k < numSubsections; ++k) {
                string subsectionTitle;
                cout << "Enter the title for subsection " << k + 1 << " in section '" << sectionTitle << "': ";
                getline(cin, subsectionTitle);

                Subsection subsection(subsectionTitle);
                section.addSubsection(subsection);
            }

            chapter.addSection(section);
        }

        book.addChapter(chapter);
    }

    cout << "\nBook structure:\n";
    book.display();

    return 0;
}

