#include <memory>
#include <string>
#include <vector>
#include <iostream>
class BaseHandler {
    public:
        std::unique_ptr<BaseHandler>& set_next(std::unique_ptr<BaseHandler> next_handler) {
            next = std::move(next_handler);
            return next;
        }

        virtual void handle(std::vector<std::string>& target) = 0;

        void run(std::vector<std::string>& target) {
            BaseHandler* handle_ptr = this;
            while(handle_ptr) {
                handle_ptr->handle(target);
                handle_ptr = handle_ptr->next.get();
            }
        }
        virtual ~BaseHandler() {};
    private:
        std::unique_ptr<BaseHandler> next;
};

class FirstHandler: public BaseHandler {
    public:
        void handle(std::vector<std::string>& target) {
            target.push_back("First type element");
        }
};

class SecondHandler: public BaseHandler {
    public:
        void handle(std::vector<std::string>& target) {
            target.push_back("Second type element");
        }
};

class ThirdHandler: public BaseHandler {
    public:
        void handle(std::vector<std::string>& target) {
            target.push_back("Third type element");
        }
};

int main() {
    std::unique_ptr<BaseHandler> a = std::make_unique<FirstHandler>();
    a->set_next(std::make_unique<FirstHandler>())
        ->set_next(std::make_unique<FirstHandler>())
        ->set_next(std::make_unique<SecondHandler>())
        ->set_next(std::make_unique<ThirdHandler>());

    std::vector<std::string> target{"<start>"};
    a->run(target);

    for(auto& str: target) {
        std::cout<<str<<" \n";
    }
    return 0;
}