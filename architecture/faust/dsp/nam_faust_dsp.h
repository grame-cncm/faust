/************************** BEGIN nam_faust_dsp.h *****************************
 FAUST Architecture File
 Copyright (C) 2026 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ***************************************************************************/

#pragma once

#include <cstdlib>
#include <memory>
#include <string>

#include "nam_c_api.h"

#include "faust/dsp/dsp.h"
#include "faust/gui/UI.h"
#include "faust/gui/meta.h"

namespace nam {
namespace faust {

    class NAMFaustDSP : public dsp {
       public:
        explicit NAMFaustDSP(const std::string& model_path = DefaultModelPath())
            : m_model_path(model_path)
        {
        }

        NAMFaustDSP(const NAMFaustDSP& other)
            : m_sample_rate(other.m_sample_rate),
              m_max_block_size(other.m_max_block_size),
              m_model_path(other.m_model_path),
              m_last_error(other.m_last_error)
        {
        }

        NAMFaustDSP& operator=(const NAMFaustDSP& other)
        {
            if (this == &other) {
                return *this;
            }
            unloadModel(false);
            m_sample_rate    = other.m_sample_rate;
            m_max_block_size = other.m_max_block_size;
            m_model_path     = other.m_model_path;
            m_last_error     = other.m_last_error;
            return *this;
        }

        ~NAMFaustDSP() override { unloadModel(false); }

        bool isLoaded() const { return m_model != nullptr; }

        const std::string& lastError() const { return m_last_error; }

        int getNumInputs() override { return m_model ? nam_num_input_channels(m_model.get()) : 1; }

        int getNumOutputs() override { return m_model ? nam_num_output_channels(m_model.get()) : 1; }

        void buildUserInterface(UI* ui_interface) override
        {
            std::string  display_name = m_model_path;
            const size_t pos          = m_model_path.find_last_of("/\\");
            if (pos != std::string::npos && pos + 1 < m_model_path.size()) {
                display_name = m_model_path.substr(pos + 1);
            }
            if (display_name.empty()) {
                display_name = "NAM";
            }

            ui_interface->openHorizontalBox(display_name.c_str());
            ui_interface->closeBox();
        }

        int getSampleRate() override { return m_sample_rate; }

        void init(int sample_rate) override
        {
            instanceInit(sample_rate);

            if (!m_model && !m_model_path.empty()) {
                if (!loadModel(m_model_path)) {
                    m_last_error =
                        nam_get_last_error() ? nam_get_last_error() : "Failed to load NAM model";
                }
            }
        }

        void instanceInit(int sample_rate) override
        {
            instanceConstants(sample_rate);
            instanceResetUserInterface();
            instanceClear();
        }

        void instanceConstants(int sample_rate) override
        {
            m_sample_rate = sample_rate;
            if (m_model) {
                nam_reset(m_model.get(), static_cast<double>(sample_rate), m_max_block_size);
            }
        }

        void instanceResetUserInterface() override {}

        void instanceClear() override
        {
            if (m_model) {
                nam_reset(m_model.get(), static_cast<double>(m_sample_rate), m_max_block_size);
            }
        }

        NAMFaustDSP* clone() override { return new NAMFaustDSP(*this); }

        void metadata(Meta* meta) override
        {
            meta->declare("author", "NeuralAmpModeler");
            meta->declare("description", "NAM C API wrapper implementing Faust dsp interface");
        }

        // Simplified: assume model is loaded and channel/sample types match.
        void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) override
        {
            nam_process(m_model.get(), reinterpret_cast<nam_sample_t**>(inputs),
                        reinterpret_cast<nam_sample_t**>(outputs), count);
        }

       private:
        struct ModelDeleter {
            void operator()(nam_model_t* model) const { nam_destroy_model(model); }
        };

        static std::string DefaultModelPath()
        {
            const char* env = std::getenv("NAM_MODEL_PATH");
            return env != nullptr ? std::string(env) : std::string();
        }

        bool loadModel(const std::string& model_path)
        {
            m_model_path = model_path;
            unloadModel(false);

            nam_model_t* raw = nullptr;
            if (nam_create_model_from_file(model_path.c_str(), &raw) != NAM_STATUS_OK ||
                raw == nullptr) {
                m_last_error = nam_get_last_error() ? nam_get_last_error() : "Failed to load NAM model";
                return false;
            }

            m_model.reset(raw);
            m_last_error.clear();
            nam_reset(m_model.get(), static_cast<double>(m_sample_rate), m_max_block_size);
            return true;
        }

        void unloadModel(bool clear_path)
        {
            m_model.reset();
            if (clear_path) {
                m_model_path.clear();
            }
            m_max_block_size = 4096;
        }

        std::unique_ptr<nam_model_t, ModelDeleter> m_model;
        int                                        m_sample_rate    = 48000;
        int                                        m_max_block_size = 4096;
        std::string                                m_model_path;
        std::string                                m_last_error;
    };

    }  // namespace faust
    
}  // namespace nam

/************************** END nam_faust_dsp.h **************************/
