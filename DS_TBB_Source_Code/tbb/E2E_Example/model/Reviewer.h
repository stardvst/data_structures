#pragma once

#include <string>

struct ReviewerName {
    ReviewerName() {}
    ReviewerName(const ReviewerName& other)
        : Title(other.Title),
        FirstName(other.FirstName),
        LastName(other.LastName),
        Suffix(other.Suffix) {}

    ReviewerName(ReviewerName&& other)
        : Title(std::move(other.Title)),
        FirstName(std::move(other.FirstName)),
        LastName(std::move(other.LastName)),
        Suffix(std::move(other.Suffix)) {}

    std::string Title;
    std::string FirstName;
    std::string LastName;
    std::string Suffix;
};

struct ReviewerAddress {
    ReviewerAddress() {}
    ReviewerAddress(const ReviewerAddress&& other)
        : Address1(other.Address1),
        Address2(other.Address2),
        City(other.City),
        State(other.State),
        Zip5(other.Zip5) {}

    ReviewerAddress(ReviewerAddress&& other)
        : Address1(std::move(other.Address1)),
        Address2(std::move(other.Address2)),
        City(std::move(other.City)),
        State(std::move(other.State)),
        Zip5(std::move(other.Zip5)) {}

    std::string Address1;
    std::string Address2;
    std::string City;
    std::string State;
    std::string Zip5;
};

struct Reviewer {
    Reviewer() {}

    Reviewer(const Reviewer& other)
        : Name(other.Name),
        Address(other.Address),
        Phone(other.Phone),
        Email(other.Email)
    {}


    Reviewer(Reviewer&& other)
        : Name(std::move(other.Name)),
        Address(std::move(other.Address)),
        Phone(std::move(other.Phone)),
        Email(std::move(other.Email))
    {}

    ReviewerName Name;
    ReviewerAddress Address;
    std::string Phone;
    std::string Email;
};

class ReviewContent {
public:
    ReviewContent() : Sentiment(0.0) {}

    ReviewContent(ReviewContent&& other) 
    : Content(std::move(other.Content)),
      Sentiment(other.Sentiment) 
    {}

    ReviewContent(const ReviewContent& other)
        : Content(other.Content),
        Sentiment(other.Sentiment)
    {}

    std::string Content;
    double Sentiment;
};

std::ostream& operator<<(std::ostream& strm, const ReviewerName& name);
std::ostream& operator<<(std::ostream& strm, const ReviewerAddress& address);
std::ostream& operator<<(std::ostream& strm, const Reviewer& reviewer);
std::ostream& operator<<(std::ostream& strm, const ReviewContent& content);