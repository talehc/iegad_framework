/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _ACTIVEMQ_TRANSPORT_TRANSPORTLISTENER_H_
#define _ACTIVEMQ_TRANSPORT_TRANSPORTLISTENER_H_

#include <activemq/util/Config.h>
#include <activemq/commands/Command.h>
#include <decaf/lang/Exception.h>
#include <decaf/lang/Pointer.h>

namespace activemq{
namespace transport{

    // Forward declarations.
    class Transport;

    using decaf::lang::Pointer;
    using activemq::commands::Command;

    /**
     * A listener of asynchronous exceptions from a command transport object.
     */
    class AMQCPP_API TransportListener {
    public:

        virtual ~TransportListener() {}

        /**
         * Event handler for the receipt of a command.  The transport passes
         * off all received commands to its listeners, the listener then owns
         * the Object.  If there is no registered listener the Transport deletes
         * the command upon receipt.
         *
         * @param command
         *      The received command object.
         */
        virtual void onCommand(const Pointer<Command> command) = 0;

        /**
         * Event handler for an exception from a command transport.
         *
         * @param ex
         *      The exception being propagated to this listener to handle.
         */
        virtual void onException(const decaf::lang::Exception& ex) = 0;

        /**
         * The transport has suffered an interruption from which it hopes to recover
         */
        virtual void transportInterrupted() = 0;

        /**
         * The transport has resumed after an interruption
         */
        virtual void transportResumed() = 0;

    };

}}

#endif /*_ACTIVEMQ_TRANSPORT_TRANSPORTLISTENER_H_*/
