#include "anims.h"

Anims::Anims(Model *model)
    : model(model),
      userdata(nullptr),
      function_ptr(nullptr),
      is_done_finished(false) {}

bool Anims::is_done() {
  if (is_done_finished) {
    return true;
  }
  bool result = is_done_impl();
  if (result) {
    if (function_ptr) {
      function_ptr(userdata);
    }
    is_done_finished = true;
  }
  return result;
}

void Anims::reset_is_done() { is_done_finished = false; }

void Anims::set_end_callback(Anims::FP fp, void *ud) {
  userdata = ud;
  function_ptr = fp;
}
