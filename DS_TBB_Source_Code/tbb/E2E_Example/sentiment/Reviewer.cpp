#pragma once

#include <string>
#include <ostream>
#include "Model\Reviewer.h"

std::ostream& operator<<(std::ostream& strm, const ReviewerName& name) {
    if (!name.Title.empty()) {
        strm << name.Title << " ";
    }

    strm << name.FirstName << " " << name.LastName;

    if (!name.Suffix.empty()) {
        strm << " " << name.Suffix;
    }

    return strm;
}

std::ostream& operator<<(std::ostream& strm, const ReviewerAddress& address) {
    if (!address.Address1.empty()) {
        strm << address.Address1 << std::endl;
    }

    if (!address.Address2.empty()) {
        strm << address.Address2 << std::endl;
    }

    strm << address.City << ", " << address.State << " " << address.Zip5;

    return strm;
}

std::ostream& operator<<(std::ostream& strm, const Reviewer& reviewer) {
    strm << reviewer.Name << std::endl;
    strm << reviewer.Address << std::endl;
    strm << reviewer.Phone << std::endl;
    strm << reviewer.Email;

    return strm;
}

std::ostream& operator<<(std::ostream& strm, const ReviewContent& content) {
    strm << content.Content << std::endl;
    strm << content.Sentiment;

    return strm;
}