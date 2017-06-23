//------------------------------------------------------------------------------
// Copyright (c) 2016 by contributors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//------------------------------------------------------------------------------

/*
Author: Chao Ma (mctt90@gmail.com)

This file tests the Nesterov updater.
*/

#include "gtest/gtest.h"

#include "src/base/common.h"

#include "src/updater/updater.h"
#include "src/updater/nesterov_updater.h"

namespace xLearn {

HyperParam param;
const int kLength = _MMX_INCREMENT * 1000000;
const int kFactor = _MMX_INCREMENT * 3;

class NesterovTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    param.learning_rate = 0.1;
    param.decay_rate = 1.0;
    param.num_param = kLength;
  }
};

TEST_F(NesterovTest, update_func) {
  Model model(kLength, false);
  std::vector<real_t> grad_vec(kLength, 1.0);
  std::vector<real_t>* w = model.GetParameter();
  Nesterov updater;
  updater.Initialize(param);
  for (int i = 0; i < kLength; ++i) {
    updater.Update(i, grad_vec[i], *w);
  }
  for (int i = 0; i < kLength; ++i) {
    EXPECT_EQ((*w)[i], (real_t)(-0.2));
  }
}

TEST_F(NesterovTest, batch_update_func) {
  std::vector<real_t> K(kFactor, 0.0);
  std::vector<real_t> grad_vec(kFactor, 1.0);
  Nesterov updater;
  updater.Initialize(param);
  updater.BatchUpdate(grad_vec, 0, K);
  for (int i = 0; i < kFactor; ++i) {
    EXPECT_EQ(K[i], (real_t)(-0.2));
  }
}

} // namespace xLearn
