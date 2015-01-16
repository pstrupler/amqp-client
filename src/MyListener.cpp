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
#include <string>

#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <SimpleAmqpClient/BasicMessage.h>

#include "MyListener.hpp"

MyListener::MyListener (
        std::string host,
        int port,
        std::string user,
        std::string password,
        std::string vHost,
        std::string exchange,
        std::string routingKey) {

   connectionData_.host = host;
   connectionData_.port = port;
   connectionData_.user = user;
   connectionData_.password = password;
   connectionData_.vHost = vHost;
   connectionData_.exchange = exchange;
   connectionData_.routingKey = routingKey;
}

void MyListener::run()
{
  std::ofstream file( "/home/pstrupler/Desktop/log" );
  file << "Listener" << std::endl;
  file << "\t" << "host: " << connectionData_.host << std::endl;
  file << "\t" << "port: " << connectionData_.port << std::endl;
  file << "\t" << "user: " << connectionData_.user << std::endl;
  file << "\t" << "password: " << connectionData_.password << std::endl;
  file << "\t" << "vHost: " << connectionData_.vHost << std::endl;
  file << "\t" << "exchange: " << connectionData_.exchange << std::endl;
  file << "\t" << "routingKey: " << connectionData_.routingKey << std::endl;
  file.flush();

  try
  {
    file << "AmqpClient::Channel::Create" << std::endl;
    file.flush();
    AmqpClient::Channel::ptr_t channelPtr =
      AmqpClient::Channel::Create(
        connectionData_.host,
        connectionData_.port,
        connectionData_.user,
        connectionData_.password,
        connectionData_.vHost
      );

    file << "DeclareQueue" << std::endl;
    file.flush();
    std::string queueName = channelPtr->DeclareQueue( std::string() );
    file << "\t" << "queue: " << queueName << std::endl;
    file.flush();

    file << "BindQueue" << std::endl;
    file.flush();
    channelPtr->BindQueue(
      queueName,
      connectionData_.exchange,
      connectionData_.routingKey
    );

    file << "BasicConsume" << std::endl;
    file.flush();
    std::string consumer_tag =
      channelPtr->BasicConsume( queueName, std::string() );
    file << "\t" << "tag: " << consumer_tag << std::endl;
    file.flush();

    file << "BasicConsumeMessage" << std::endl;
    file.flush();
    AmqpClient::Envelope::ptr_t envelopePtr =
      channelPtr->BasicConsumeMessage( consumer_tag );
    file << "\t" << "body: " << envelopePtr->Message()->Body() << std::endl;
    file.flush();

    file << "BasicCancel" << std::endl;
    file.flush();
    channelPtr->BasicCancel( consumer_tag );
  }
  catch ( AmqpClient::AmqpException const& exception )
  {
    file << "Exception: " << typeid( exception ).name() << std::endl;
    file << "\t" << "what: " << exception.what() << std::endl;
    file << "\t" << "is_soft_error: " << exception.is_soft_error() << std::endl;
    file << "\t" << "reply_code: " << exception.reply_code() << std::endl;
    file << "\t" << "class_id: " << exception.class_id() << std::endl;
    file << "\t" << "method_id: " << exception.method_id() << std::endl;
    file << "\t" << "reply_text: " << exception.reply_text() << std::endl;
  }
  catch ( std::exception const& exception )
  {
    file << "Exception: " << typeid( exception ).name() << std::endl;
    file << "\t" << "what: " << exception.what() << std::endl;
  }
  catch ( ... )
  {
    file << "Exception: ..." << std::endl;
  }
}
