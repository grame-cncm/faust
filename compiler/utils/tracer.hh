#include <iostream>
#include <sstream>
#include <string>

class NullTracer {
   public:
    // Conserve la même signature de constructeur,
    // mais ignore complètement les arguments.
    explicit NullTracer(bool /*enabled*/ = true, std::ostream& /*out*/ = std::cerr) {}

    // Le “stream” factice : tous les << sont des no-ops
    struct Stream {
        template <typename T>
        Stream& operator<<(const T&)
        {
            return *this;
        }
        Stream& operator<<(std::ostream& (*)(std::ostream&)) { return *this; }
    };

    // Méthodes de l’API
    Stream enter() { return Stream(); }
    Stream log() { return Stream(); }
    Stream exit() { return Stream(); }
};

class Tracer {
   public:
    explicit Tracer(std::ostream& out = std::cerr) : out_(out), indent_level_(0) {}

    // --- base générique sans virtuel, gère used_/flushed_
    template <typename Derived>
    class StreamBase {
       public:
        explicit StreamBase(Tracer& tracer) : tracer_(tracer), used_(false), flushed_(false) {}
        ~StreamBase()
        {
            if (used_ && !flushed_) {
                static_cast<Derived*>(this)->do_flush();
            }
        }

        template <typename T>
        Derived& operator<<(const T& v)
        {
            prepare();
            buf_ << v;
            return *static_cast<Derived*>(this);
        }

        Derived& operator<<(std::ostream& (*manip)(std::ostream&))
        {
            prepare();
            buf_ << manip;
            if (manip == static_cast<std::ostream& (*)(std::ostream&)>(std::endl)) {
                static_cast<Derived*>(this)->do_flush();
            }
            return *static_cast<Derived*>(this);
        }

       protected:
        Tracer&            tracer_;
        bool               used_;
        bool               flushed_;
        std::ostringstream buf_;

        void prepare()
        {
            if (!used_) {
                static_cast<Derived*>(this)->do_prepare();
                used_ = true;
            }
        }
    };

    // --- StreamEnter : ajoute "ENTER: "
    class StreamEnter : public StreamBase<StreamEnter> {
       public:
        using StreamBase<StreamEnter>::StreamBase;
        void do_prepare()
        {
            tracer_.print_indent();
            tracer_.out_ << "ENTER: ";
        }
        void do_flush()
        {
            tracer_.out_ << this->buf_.str();
            tracer_.out_.flush();
            this->buf_.str("");
            this->buf_.clear();
            tracer_.indent_level_++;
            this->flushed_ = true;
        }
    };

    // --- StreamLog : ajoute "LOG: "
    class StreamLog : public StreamBase<StreamLog> {
       public:
        using StreamBase<StreamLog>::StreamBase;
        void do_prepare()
        {
            tracer_.print_indent();
            tracer_.out_ << "LOG  : ";
        }
        void do_flush()
        {
            tracer_.out_ << this->buf_.str();
            tracer_.out_.flush();
            this->buf_.str("");
            this->buf_.clear();
            this->flushed_ = true;
        }
    };

    // --- StreamExit : ajoute "EXIT: "
    class StreamExit : public StreamBase<StreamExit> {
       public:
        using StreamBase<StreamExit>::StreamBase;
        void do_prepare()
        {
            if (tracer_.indent_level_ > 0) {
                tracer_.indent_level_--;
            }
            tracer_.print_indent();
            tracer_.out_ << "EXIT : ";
        }
        void do_flush()
        {
            tracer_.out_ << this->buf_.str();
            tracer_.out_.flush();
            this->buf_.str("");
            this->buf_.clear();
            this->flushed_ = true;
        }
    };

    // Accès aux wrappers
    StreamEnter enter() { return StreamEnter(*this); }
    StreamLog   log() { return StreamLog(*this); }
    StreamExit  exit() { return StreamExit(*this); }

   private:
    std::ostream& out_;
    int           indent_level_;

    void print_indent() { out_ << std::string(indent_level_ * 4, ' '); }
};
