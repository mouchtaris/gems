# frozen_string_literal: true

require 'spec_helper'

require 'mastoras/facade'

RSpec.describe Mastoras::Facade do
  describe '#initialize (construction)' do
    subject(:construction) { described_class.new(*construction_arguments) }

    describe 'with a Pathname' do
      let(:construction_arguments) { [Pathname.new('/somewhere/')] }
      it { expect { subject }.not_to raise_error }
    end

    describe 'with a String' do
      let(:construction_arguments) { ['/somewhere/'] }
      it { expect { subject }.to raise_error ArgumentError }
    end
  end
end
