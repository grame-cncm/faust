Faust to Flash conversion scripts

Travis Skare / skare@stanford.edu
Project site: http://ccrma.stanford.edu/~travissk/faustflash
Personal site: http://www.travisskare.com

Introduction
------------
The enclosed code can be used with your own Faust DSP scripts, the Faust
compiler, Adobe Alchemy/Flash/Flex to produce Flash .swf files. While the
process is designed to be able to display DSP examples online, it can be used
for multimedia demos, audio effects in games, etc.

Please note that the code is functional, but has some known technical issues
and a list of areas for improvement. The C++ code in particular needs some
cleanup; large sections were thrown together to fix bugs and get communication
from ActionScript->C++ working (this was my first Alchemy project).

Feel free to email me with questions, comments, or suggestions for improvement.


Changelog (Current Version: 0.1)
---------
0.1: Proof of concept - functional but needs some cleanup.


License
-------
As my intent is to polish this up and submit the architecture file as a patch
to Faust (if the project desires it) it's tentatively GPL. See the file COPYING.


The Unfortunately Obligatory License Agreement (and other short stories):
------------------------------------------------------------------------
THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
