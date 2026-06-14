#include <httplib.h>

#include "daemon_endpoints.hpp"

int main(int argc, char** argv) {
  httplib::Server svr;

  svr.Post("/start", [](const httplib::Request& req, httplib::Response& resp) {
    StartEP(req.body);
    resp.set_content("Success", "text/plain");
  });

  svr.Post("/stop", [](const httplib::Request& req, httplib::Response& resp) {
    StopEP(req.body);
    resp.set_content("Success", "text/plain");
  });

  svr.Post("/status", [](const httplib::Request& req, httplib::Response& resp) {
    resp.set_content(StatusEP(req.body), "application/json");
  });

  svr.Post("/poweroff", [](const httplib::Request& req, httplib::Response& resp) {
    std::cout << "Power off" << std::endl;
    throw std::runtime_error("Power off");
  });
  svr.set_exception_handler([](const auto& req, auto& res, std::exception_ptr ep) { std::rethrow_exception(ep); });

  svr.listen("0.0.0.0", 8080);
}
