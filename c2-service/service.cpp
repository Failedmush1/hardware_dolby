/*
 * Copyright (C) 2026 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "vendor.dolby.media.c2@1.0-service"

#include <android-base/logging.h>
#include <binder/ProcessState.h>
#include <codec2/hidl/1.0/ComponentStore.h>
#include <hidl/HidlTransportSupport.h>
#include <log/log.h>
#include <signal.h>

#include <C2Component.h>
#include <memory>

namespace android {
    std::shared_ptr<C2ComponentStore> GetCodec2DolbyComponentStore();
}

int main(int /* argc */, char** /* argv */) {
    ALOGD("vendor.dolby.media.c2@1.0-service starting...");
    signal(SIGPIPE, SIG_IGN);
    android::ProcessState::initWithDriver("/dev/vndbinder");
    android::ProcessState::self()->startThreadPool();
    android::hardware::configureRpcThreadpool(8, true /* callerWillJoin */);

    std::shared_ptr<C2ComponentStore> store = android::GetCodec2DolbyComponentStore();
    if (!store) {
        ALOGE("Cannot get Dolby Codec2 component store.");
        return 1;
    }

    using namespace ::android::hardware::media::c2::V1_0;
    android::sp<IComponentStore> c2store = new utils::ComponentStore(store);
    if (c2store == nullptr) {
        ALOGE("Cannot create Codec2's IComponentStore service.");
        return 1;
    }

    if (c2store->registerAsService("default1") != android::OK) {
        ALOGE("Cannot register Dolby Codec2 service with instance name \"default1\".");
        return 1;
    }

    ALOGI("Dolby Codec2 service registered with instance name \"default1\".");
    android::hardware::joinRpcThreadpool();
    return 0;
}
