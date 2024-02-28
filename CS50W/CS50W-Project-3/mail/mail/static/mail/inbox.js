document.addEventListener('DOMContentLoaded', function () {

  // Use buttons to toggle between views
  document.querySelector('#inbox').addEventListener('click', () => load_mailbox('inbox'));
  document.querySelector('#sent').addEventListener('click', () => load_mailbox('sent'));
  document.querySelector('#archived').addEventListener('click', () => load_mailbox('archive'));
  document.querySelector('#compose').addEventListener('click', compose_email);

  // By default, load the inbox
  load_mailbox('inbox');
});

function compose_email() {

  // Show compose view and hide other views
  document.querySelector('#emails-view').style.display = 'none';
  document.querySelector('#compose-view').style.display = 'block';

  emailContainer = document.querySelector('.emailContainer')
  if (emailContainer) {
    emailContainer.remove();
  }

  // Clear out composition fields
  composeRecipients = document.querySelector('#compose-recipients')
  composeRecipients.value = '';
  composeSubject = document.querySelector('#compose-subject')
  composeSubject.value = '';
  composeBody = document.querySelector('#compose-body')
  composeBody.value = '';

  document.querySelector('#compose-btn').onclick = () => {
    email = {
      recipients: composeRecipients.value,
      subject: composeSubject.value,
      body: composeBody.value
    }
    fetch('/emails', {
      method: 'POST',
      body: JSON.stringify(email)
    })
      .then(response => response.json())
      .then(result => {
        // Print error if it is returned and loads the mailbox AFTER the response.
        if (result.error != undefined) {
          alert(result.error)
          return false
        };
        load_mailbox('sent');
      });
    // Prevents default behavior of button.
    return false
  };
}

function create_element(element_text, bold) {
  element = document.createElement('span');
  if (bold) {
    element.className = "bold-content";
  }
  else {
    element.className = "plain-content";
  };
  element.innerHTML = element_text;
  return element
}


function createArchiveButton(email) {
  user = document.querySelector('h2').innerHTML
  if (user != email.sender) {
    new_button = document.createElement('button');
    new_button.className = "btn btn-sm btn-outline-primary";
    new_button.id = "archive_button"
    if (!email.archived) {
      new_button.innerHTML = "Archive"
    }
    else {
      new_button.innerHTML = "Unarchive"
    }
    new_button.addEventListener('click', () => {
      button_select = document.querySelector('#archive_button')
      if (button_select.innerHTML === "Archive") {
        fetch(`/emails/${email.id}`, {
          method: 'PUT',
          body: JSON.stringify({
            archived: true
          })
        })
          .then(() => {
            //Added dynamic function to the button before noticing that the requirement is to reload the inbox page.
            //button_select.innerHTML = "Unarchive";
            load_mailbox("inbox")
          })
      }
      else {
        fetch(`/emails/${email.id}`, {
          method: 'PUT',
          body: JSON.stringify({
            archived: false
          })
        })
          .then(() => {
            //button_select.innerHTML = "Archive";
            load_mailbox("inbox")
          })

      }
    })
    return new_button
  }
  else {
    return ""
  }
}

function handleReply(event) {
  email = event.currentTarget.new_param
  compose_email()
  composeRecipients = document.querySelector('#compose-recipients')
  composeRecipients.value = `${email.sender}`;
  composeSubject = document.querySelector('#compose-subject')
  composeSubject.value = `Re: ${email.subject}`;
  composeBody = document.querySelector('#compose-body')
  composeBody.value = `On ${email.timestamp} ${email.sender} wrote: ${email.body}`;

}

function loadEmail(emailId) {
  document.querySelector('#emails-view').style.display = 'none';
  document.querySelector('#compose-view').style.display = 'none';
  fetch(`/emails/${emailId}`)
    .then(response => response.json())
    .then(email => {
      // Create all elements
      const emailContent = document.createElement('div');
      emailContent.className = "emailContainer"

      From = create_element("From: ", true)
      Sender = create_element(`${email.sender} <br>`);
      To = create_element("To: ", true)
      Recipient = create_element(`${email.recipients} <br>`);
      Subject = create_element("Subject: ", true);
      Title = create_element(`${email.subject} <br>`);
      Timestamp = create_element("Timestamp: ", true);
      Time = create_element(`${email.timestamp} <br>`);

      button = document.createElement('button');
      button.className = "btn btn-sm btn-outline-primary";
      button.innerHTML = "Reply"
      button.new_param = email
      button.addEventListener('click', handleReply)

      Body = create_element(`${email.body}`)

      archive_button = createArchiveButton(email)

      emailContent.append(From, Sender, To, Recipient, Subject, Title, Timestamp, Time, button, archive_button, document.createElement('hr'), Body)
      document.querySelector('.container').append(emailContent);
    }).then(
      fetch(`/emails/${emailId}`, {
        method: 'PUT',
        body: JSON.stringify({
          read: true
        })
      })
    );
};


function load_mailbox(mailbox) {

  // Show the mailbox and hide other views
  document.querySelector('#emails-view').style.display = 'block';
  document.querySelector('#compose-view').style.display = 'none';
  emailContainer = document.querySelector('.emailContainer')
  if (emailContainer) {
    emailContainer.remove();
  }

  // Show the mailbox name
  document.querySelector('#emails-view').innerHTML = `<h3>${mailbox.charAt(0).toUpperCase() + mailbox.slice(1)}</h3>`;

  // GET mailbox
  fetch(`/emails/${mailbox}`)
    .then(response => response.json())
    .then(emails => {
      // Creates the e-mail div for each e-mail received by the JSON
      emails.forEach(email => {
        const element = document.createElement('div');
        element.className = "email-div";
        user = document.querySelector('h2').innerHTML
        if (email.read && user != email.sender) {
          element.className = "email-div read";
        };
        senderHTML = document.createElement('span');
        senderHTML.className = "sender";
        senderHTML.innerHTML = `${email.sender}`;
        element.append(senderHTML);
        subjectHTML = document.createElement('span');
        subjectHTML.className = 'subject';
        subjectHTML.innerHTML = `${email.subject}`;
        element.append(subjectHTML);
        timestampHTML = document.createElement('span');
        timestampHTML.className = 'timestamp';
        timestampHTML.innerHTML = `${email.timestamp}`
        element.append(timestampHTML)
        element.addEventListener('click', function () {
          loadEmail(email.id);
        });
        document.querySelector('#emails-view').append(element);
      });
    });
}