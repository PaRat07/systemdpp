#include <httplib.h>

#include <rfl/json.hpp>
#include <rfl.hpp>

#include <commands.hpp>


int main(int argc, char** argv) {
  httplib::Server svr;

  svr.Post("/start", [](const httplib::Request& req, httplib::Response& resp) {
    auto args = rfl::json::read<std::vector<std::string>>(req.body).value();
    Start(std::move(args));
    resp.set_content("Success", "text/plain");
  });

  svr.Post("/stop", [](const httplib::Request& req, httplib::Response& resp) {
    auto args = rfl::json::read<std::vector<std::string>>(req.body).value();
    Stop(std::move(args));
    resp.set_content("Success", "text/plain");
  });

  svr.Post("/status", [](const httplib::Request& req, httplib::Response& resp) {
    auto res_body = rfl::json::write(Status(req.body));
    resp.set_content(res_body, "application/json");
  });

  svr.Post("/poweroff", [](const httplib::Request& req, httplib::Response& resp) {
    std::cout << "Power off" << std::endl;
    throw std::runtime_error("Power off");
  });
  svr.set_exception_handler([](const auto& req, auto& res, std::exception_ptr ep) { std::rethrow_exception(ep); });

  svr.listen("0.0.0.0", 8080);
}
