/*
 * Copyright (c) 2014, Autonomous Systems Lab, ETH Zurich, Switzerland
 *
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */


#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "MyListener.hpp"


int main() {
  MyListener * listener = new MyListener("localhost", 5672, "guest", "guest", "/", "logs", "");

  listener->run();
}



/*
int main() {

	char* szBroker = getenv("AMQP_BROKER");
	Channel::ptr_t channel;
	if (szBroker != NULL)
	  channel = Channel::Create(szBroker);
	else
	  channel = Channel::Create("localhost");

	channel->DeclareQueue("alanqueue");
	channel->BindQueue("alanqueue", "amq.direct", "alankey");

	BasicMessage::ptr_t msg_in = BasicMessage::Create();

	msg_in->Body("This is a small message.");

	std::cerr << "Sending messages....";
	{

    for (int i = 0; i < 10; ++i)
    {
      channel->BasicPublish("amq.direct", "alankey", msg_in);
    }
	}
	std::cerr << "done.\n";

	std::cerr << "Receiving messages....";
	std::string consumer = channel->BasicConsume("alanqueue", "consumertag");
	Envelope::ptr_t envelope = channel->BasicConsumeMessage(consumer);

	{
    for (int i = 0; i < 10; ++i)
    {
      envelope = channel->BasicConsumeMessage(consumer);
      std::cerr << envelope->Message() << "\n";
    }
	}
	std::cerr << "done.\n";

	return 0;
}

*/
