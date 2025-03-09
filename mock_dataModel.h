#pragma once
#include <string>
#include <vector>

namespace MOCK {
    struct User {
        int user_id;
        std::string username;
        std::string password_hash;
        std::string role = "guest";  // e.g., "editor", "journalist", "subscriber", "guest"
    };

    struct Article {
        int article_id;
        std::string title;
        std::string content;
        int author_id;
    };

    struct Comment {
        int comment_id;
        std::string content;
        int article_id;
        int user_id;
    };

    // Function declarations
    User getUserFromRequest();
    User getUserByUsername(const std::string& username); // Added missing function
}
