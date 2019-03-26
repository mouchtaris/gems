# frozen_string_literal: true

require 'spec_helper'
require 'mastoras/version'

RSpec.describe Mastoras::Version do
  local_subject = described_class
  subject(:version) { local_subject }

  it 'exists' do
  end

  describe local_subject::VERSION do
    subject(:value) { version::VERSION }
    it { is_expected.to eq '0.0.0' }
  end
end
